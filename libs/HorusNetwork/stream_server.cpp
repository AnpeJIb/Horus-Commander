#include "stream_server.h"

#include <QDebug>
#include <boost/bind.hpp>

const QString c_address = "localhost";
const QString c_port = "20001";

StreamServer::StreamServer(const boost::shared_ptr<StreamServerConnectionManager> &manager)
    : m_manager(manager),
      m_io_service(),
      m_signals(m_io_service),
      m_acceptor(m_io_service),
      m_new_connection(),
      m_address(c_address),
      m_port(c_port),
      m_running(false)
{
    initSignals();
}

StreamServer::StreamServer(
        const QString &address,
        const boost::shared_ptr<StreamServerConnectionManager>& manager)
    : m_manager(manager),
      m_io_service(),
      m_signals(m_io_service),
      m_acceptor(m_io_service),
      m_new_connection(),
      m_address(address),
      m_port(c_port),
      m_running(false)
{
    initSignals();
}

StreamServer::StreamServer(const QString &address,
        const QString &port,
        const boost::shared_ptr<StreamServerConnectionManager> &manager)
    : m_manager(manager),
      m_io_service(),
      m_signals(m_io_service),
      m_acceptor(m_io_service),
      m_new_connection(),
      m_address(address),
      m_port(port),
      m_running(false)
{
    initSignals();
}

void StreamServer::initSignals()
{
    m_signals.add(SIGINT);
    m_signals.add(SIGTERM);
#if defined(SIGQUIT)
    m_signals.add(SIGQUIT);
#endif
    m_signals.async_wait(boost::bind(&StreamServer::handleStop, this));
}

void StreamServer::setAddress(const QString &value)
{
    m_address = value;
}

void StreamServer::setPort(const QString &value)
{
    m_port = value;
}

void StreamServer::start(const QString &address)
{
    if (m_running) return;
    setAddress(address);
    start();
}

void StreamServer::start(const QString &address, const QString &port)
{
    if (m_running) return;
    setPort(port);
    start(address);
}

void StreamServer::start()
{
    if (m_running) return;
    m_running = true;

    boost::asio::ip::tcp::resolver resolver(m_io_service);
    boost::asio::ip::tcp::resolver::query query(m_address.toStdString(), m_port.toStdString());
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    m_acceptor.open(endpoint.protocol());
    m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor.bind(endpoint);
    m_acceptor.listen();
    startAccept();

    m_io_service.run();    
}

void StreamServer::stop()
{
    if (m_running == false) return;
    m_manager->kickAll();
    m_io_service.stop();
    m_running = false;
}

void StreamServer::startAccept()
{
    m_new_connection.reset(m_manager->getNewConnection(m_io_service, m_manager));
    m_acceptor.async_accept(m_new_connection->socket(),
                            boost::bind(&StreamServer::handleAccept, this,
                                        boost::asio::placeholders::error));
}

void StreamServer::handleAccept(const boost::system::error_code &e)
{
    if (m_manager->isNewConnectionAvailable() == false)
    {
        m_new_connection->socket().cancel();
        return;
    }

    if (m_acceptor.is_open()==false)
        return;

    if (!e)
        m_manager->join(m_new_connection);

    startAccept();
}

void StreamServer::handleStop()
{
    m_acceptor.close();
    stop();
}

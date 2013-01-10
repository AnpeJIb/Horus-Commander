#include "stream_client.h"

#include <boost/bind.hpp>

StreamClient::StreamClient(boost::asio::io_service& io_service)
    : StreamConnection(io_service),
      m_signals(io_service)
{
    m_signals.add(SIGINT);
    m_signals.add(SIGTERM);
#if defined(SIGQUIT)
    m_signals.add(SIGQUIT);
#endif
    m_signals.async_wait(boost::bind(&StreamClient::handleInterrupt, this));
}

void StreamClient::connect(const QString &address, const QString &port)
{
    if (m_socket.is_open()) return;

    m_exit_result = UNDEFINED;

    tcp::resolver resolver(m_signals.get_io_service());
    tcp::resolver::query query(address.toStdString(), port.toStdString());
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::endpoint endpoint = *endpoint_iterator;
    m_socket.async_connect(endpoint,
                          boost::bind(&StreamClient::handleConnect, this,
                                      boost::asio::placeholders::error, ++endpoint_iterator));
}

void StreamClient::handleConnect(const boost::system::error_code& error,
                                 tcp::resolver::iterator endpoint_iterator)
{
    if (!error)
    {
        emit connectionSuccess();
        newReadCycle();
    } else if (endpoint_iterator != tcp::resolver::iterator()) {
        m_socket.close();
        tcp::endpoint endpoint = *endpoint_iterator;
        m_socket.async_connect(endpoint,
                              boost::bind(&StreamClient::handleConnect, this,
                                          boost::asio::placeholders::error, ++endpoint_iterator));
    } else {
        m_exit_result = CONNECTION_FAILED;
        m_socket.close();
        emit connectionFailure();
    }
}

void StreamClient::disconnect()
{
    if (m_socket.is_open() == false) return;
    stop();
    m_exit_result = STOPPED_NORMALLY;
    emit disconnected();
}

void StreamClient::onErrorOccured()
{
    handleInterrupt();
}

void StreamClient::handleInterrupt()
{
    if (m_socket.is_open() == false) return;
    stop();
    m_exit_result = CONNECTION_LOST;
    emit connectionLost();
}

StreamClient::EXIT_RESULT StreamClient::exitResult()
{
    return (StreamClient::EXIT_RESULT) m_exit_result;
}

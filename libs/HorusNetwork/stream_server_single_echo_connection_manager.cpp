#include "stream_server_single_echo_connection_manager.h"
#include "stream_server_echo_connection.h"

StreamServerSingleEchoConnectionManager::StreamServerSingleEchoConnectionManager()
{
    m_connection.reset();
}

void StreamServerSingleEchoConnectionManager::join(boost::shared_ptr<StreamServerConnection> connection)
{
    if (isNewConnectionAvailable() == false) return;

    m_connection = connection;
    m_connection->start();
    increaseConnections();
}

void StreamServerSingleEchoConnectionManager::leave(boost::shared_ptr<StreamServerConnection> connection)
{
    if (connection != m_connection) return;
    if (!m_connection) return;

    m_connection->stop();
    m_connection.reset();
    decreaseConnections();
}

void StreamServerSingleEchoConnectionManager::kickAll()
{
    leave(m_connection);
}

StreamServerConnection *StreamServerSingleEchoConnectionManager::getNewConnection(
        boost::asio::io_service &io_service, const boost::shared_ptr<StreamServerConnectionManager> &manager)
{
    return new StreamServerEchoConnection(io_service, manager);
}

void StreamServerSingleEchoConnectionManager::setMaxConnections(uint value)
{
    Q_UNUSED(value)
}

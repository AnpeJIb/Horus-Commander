#include "stream_server_connection.h"

StreamServerConnection::StreamServerConnection(boost::asio::io_service &io_service,
        const boost::shared_ptr<StreamServerConnectionManager> &manager)
    : StreamConnection(io_service),
      m_manager(manager)
{
}

void StreamServerConnection::start()
{
    newReadCycle();
}

void StreamServerConnection::onErrorOccured()
{
    m_manager->leave(shared_from_this());
}

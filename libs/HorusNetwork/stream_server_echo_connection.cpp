#include "stream_server_echo_connection.h"

StreamServerEchoConnection::StreamServerEchoConnection(
        boost::asio::io_service &io_service,
        const boost::shared_ptr<StreamServerConnectionManager> &manager)
    : StreamServerConnection(io_service, manager)
{
    connect(this, SIGNAL(messageReceived(QString)),
            this, SLOT(onMessageReceived(QString)));
}

void StreamServerEchoConnection::onMessageReceived(QString msg)
{
    sendMessage(msg);
}

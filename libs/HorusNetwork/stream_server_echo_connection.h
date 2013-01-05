#ifndef STREAM_SERVER_ECHO_CONNECTION_H
#define STREAM_SERVER_ECHO_CONNECTION_H

#include "horus_network_global.h"
#include "stream_server_connection.h"

class HORUS_NETWORK_SHARED_EXPORT StreamServerEchoConnection: public StreamServerConnection
{
    Q_OBJECT
public:
    explicit StreamServerEchoConnection(boost::asio::io_service &io_service,
                                        const boost::shared_ptr<StreamServerConnectionManager>& manager);

public slots:
    void onMessageReceived(QString msg);
};

#endif // STREAM_SERVER_ECHO_CONNECTION_H

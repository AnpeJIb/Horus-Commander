#ifndef STREAM_SERVER_SINGLE_CONNECTION_MANAGER_H
#define STREAM_SERVER_SINGLE_CONNECTION_MANAGER_H

#include "stream_server_connection_manager.h"

class StreamServerSingleEchoConnectionManager: public StreamServerConnectionManager
{
public:
    StreamServerSingleEchoConnectionManager();

    void join(boost::shared_ptr<StreamServerConnection> connection);
    void leave(boost::shared_ptr<StreamServerConnection> connection);
    void kickAll();
    StreamServerConnection* getNewConnection(boost::asio::io_service &io_service,
                                             const boost::shared_ptr<StreamServerConnectionManager> &manager);

private:
    boost::shared_ptr<StreamServerConnection> m_connection;
};

#endif // STREAM_SERVER_SINGLE_CONNECTION_MANAGER_H

#ifndef STREAM_SERVER_CONNECTION_MANAGER_H
#define STREAM_SERVER_CONNECTION_MANAGER_H

#include <QtCore>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "stream_server_connection.h"

class StreamServerConnection;
class StreamServerConnectionManager;

class StreamServerConnectionManager
    : public boost::enable_shared_from_this<StreamServerConnectionManager>,
      private boost::noncopyable
{
public:
    typedef boost::shared_ptr<StreamServerConnectionManager> pointer;

    StreamServerConnectionManager();
    StreamServerConnectionManager(uint max_connections);
    virtual ~StreamServerConnectionManager(){}

    virtual void setMaxConnections(uint value);
    bool isNewConnectionAvailable();

    virtual void join(boost::shared_ptr<StreamServerConnection> connection) = 0;
    virtual void leave(boost::shared_ptr<StreamServerConnection> connection) = 0;
    virtual void kickAll() = 0;

    virtual StreamServerConnection* getNewConnection(
            boost::asio::io_service &io_service, const boost::shared_ptr<StreamServerConnectionManager>& manager) = 0;

protected:
    void increaseConnections();
    void decreaseConnections();

    uint m_max_connections;
    uint m_current_connections;
};

#endif // STREAM_SERVER_CONNECTION_MANAGER_H

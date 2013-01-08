#ifndef STREAM_SERVER_CONNECTION_H
#define STREAM_SERVER_CONNECTION_H

#include <QObject>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>

#include "stream_connection.h"
#include "stream_server_connection_manager.h"

class StreamServerConnection;
class StreamServerConnectionManager;

class StreamServerConnection
    : public StreamConnection,
      public boost::enable_shared_from_this<StreamServerConnection>,
      private boost::noncopyable
{
    Q_OBJECT
public:
    explicit StreamServerConnection(boost::asio::io_service &io_service,
                                    const boost::shared_ptr<StreamServerConnectionManager>& manager);
    virtual ~StreamServerConnection(){}

    void start();

protected:
    void onErrorOccured();

    const boost::shared_ptr<StreamServerConnectionManager>& m_manager;
};

#endif // STREAM_SERVER_CONNECTION_H

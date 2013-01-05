#ifndef STREAM_SERVER_CONNECTION_H
#define STREAM_SERVER_CONNECTION_H

#include "horus_network_global.h"

#include <QObject>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>

#include "stream_server_connection_manager.h"

class StreamServerConnection;
class StreamServerConnectionManager;

class HORUS_NETWORK_SHARED_EXPORT StreamServerConnection
    : public QObject,
      public boost::enable_shared_from_this<StreamServerConnection>,
      private boost::noncopyable
{
    Q_OBJECT
public:
    enum { max_body_length = 8192 };

    explicit StreamServerConnection(boost::asio::io_service &io_service,
                                    const boost::shared_ptr<StreamServerConnectionManager>& manager);
    virtual ~StreamServerConnection(){}

    boost::asio::ip::tcp::socket& socket() {return m_socket;}

    void start();
    void stop();

    void sendMessage(const QString& msg);

signals:
    void messageReceived(QString);

protected:
    void newReadCycle();

    void handleReadChar(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);

    boost::asio::ip::tcp::socket m_socket;
    const boost::shared_ptr<StreamServerConnectionManager>& m_manager;

    char m_rx_data[max_body_length];
    uint m_rx_data_offset;

    std::deque<QString> m_write_msgs;
};

#endif // STREAM_SERVER_CONNECTION_H

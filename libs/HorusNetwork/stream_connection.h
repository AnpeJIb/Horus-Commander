#ifndef STREAM_CONNECTION_H
#define STREAM_CONNECTION_H

#include <QObject>
#include <QString>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>

using boost::asio::ip::tcp;

class StreamConnection: public QObject
{
    Q_OBJECT
public:
    enum { max_body_length = 8192 };

    explicit StreamConnection(boost::asio::io_service &io_service);
    virtual ~StreamConnection(){}

    boost::asio::ip::tcp::socket& socket();

    void sendMessage(const QString& msg);
    void stop();

signals:
    void messageReceived(QString);

protected:
    virtual void onErrorOccured() = 0;

    void newReadCycle();
    void handleReadChar(const boost::system::error_code& error);
    void handleWrite(const boost::system::error_code& error);

    boost::asio::ip::tcp::socket m_socket;

    char m_rx_data[max_body_length];
    uint m_rx_data_offset;

    std::deque<QString> m_write_msgs;
};

#endif // STREAM_CONNECTION_H

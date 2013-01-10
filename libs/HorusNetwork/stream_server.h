#ifndef STREAM_SERVER_H
#define STREAM_SERVER_H

#include <QObject>
#include <QString>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>

#include "stream_server_connection.h"
#include "stream_server_connection_manager.h"

class StreamServer
    : public QObject,
      private boost::noncopyable
{
    Q_OBJECT
public:
    typedef boost::shared_ptr<StreamServer> pointer;

    StreamServer(boost::asio::io_service& io_service,
                 const boost::shared_ptr<StreamServerConnectionManager>& manager);
    StreamServer(const QString& address,
                 boost::asio::io_service& io_service,
                 const boost::shared_ptr<StreamServerConnectionManager> &manager);
    StreamServer(const QString& address,
                 const QString& port,
                 boost::asio::io_service& io_service,
                 const boost::shared_ptr<StreamServerConnectionManager>& manager);

    ~StreamServer(){}

    void setAddress(const QString& value);
    void setPort(const QString& value);

    void start(const QString& address);
    void start(const QString& address, const QString& port);
    void start();
    void stop();

signals:
    void startSuccess();
    void startFailure();
    void stoppedNormally();
    void interrupted();

private:
    void initSignals();
    void startAccept();
    void handleAccept(const boost::system::error_code& e);
    void handleStop();
    void doStop();

    const boost::shared_ptr<StreamServerConnectionManager>& m_manager;

    boost::asio::signal_set m_signals;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::shared_ptr<StreamServerConnection> m_new_connection;

    QString m_address;
    QString m_port;

    bool m_running;
};

#endif // STREAM_SERVER_H

#ifndef STREAM_CLIENT_H
#define STREAM_CLIENT_H

#include <QObject>
#include <QString>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>

#include "stream_connection.h"
#include "stream_defaults.h"

using boost::asio::ip::tcp;

class StreamClient;

class StreamClient
    : public StreamConnection,
      public boost::enable_shared_from_this<StreamClient>,
      private boost::noncopyable
{
    Q_OBJECT
public:
    typedef boost::shared_ptr<StreamClient> pointer;

    enum EXIT_RESULT
    {
        UNDEFINED,
        CONNECTION_FAILED,
        CONNECTION_LOST,
        STOPPED_NORMALLY
    };

    explicit StreamClient(boost::asio::io_service& io_service);
    virtual ~StreamClient(){}

    void connect(const QString& address = StreamDefaults::default_address,
                 const QString& port = StreamDefaults::default_port);
    void disconnect();

    EXIT_RESULT exitResult();

signals:
    void connectionSuccess();
    void connectionFailure();
    void connectionLost();
    void disconnected();

protected:
    void handleConnect(const boost::system::error_code& error,
                       tcp::resolver::iterator endpoint_iterator);
    void handleInterrupt();
    void onErrorOccured();

    boost::asio::signal_set m_signals;
    EXIT_RESULT m_exit_result;
};

#endif // STREAM_CLIENT_H

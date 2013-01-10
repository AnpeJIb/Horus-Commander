#ifndef EMULATOR_CONNECTION_MANAGER_H
#define EMULATOR_CONNECTION_MANAGER_H

#include <QObject>
#include <QString>

#include "stream_server_connection_manager.h"

class EmulatorConnectionManager:
        public QObject,
        public StreamServerConnectionManager
{
    Q_OBJECT
public:
    typedef boost::shared_ptr<EmulatorConnectionManager> pointer;

    EmulatorConnectionManager();

    void join(boost::shared_ptr<StreamServerConnection> connection);
    void leave(boost::shared_ptr<StreamServerConnection> connection);
    void kickAll();
    StreamServerConnection* getNewConnection(boost::asio::io_service &io_service,
                                             const boost::shared_ptr<StreamServerConnectionManager> &manager);

    void setMaxConnections(uint value);

public slots:
    void sendMessage(const QString& msg){Q_UNUSED(msg);}

signals:
    void messageReceived(QString);

private:
    boost::shared_ptr<StreamServerConnection> m_connection;
};

#endif // EMULATOR_CONNECTION_MANAGER_H

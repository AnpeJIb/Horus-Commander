#ifndef SERVER_EMULATOR_H
#define SERVER_EMULATOR_H

#include <QThread>
#include <QString>

#include "stream_server.h"
#include "emulator_connection_manager.h"

class ServerEmulator: public QThread
{
    Q_OBJECT
public:
    enum EXIT_RESULT
    {
        UNDEFINED,
        START_FAILED,
        INTERRUPTED,
        STOPPED_NORMALLY
    };

    ServerEmulator();
    void stop();

    void configure(const QString& address, const QString& port, const QString& event_log_path);

    EXIT_RESULT exitResult();

signals:
    void startSuccess();
    void startFailure();
    void stoppedNormally();
    void interrupted();

protected:
    void run();

private slots:
    void onStartSuccess();
    void onStartFailure();
    void onStoppedNormally();
    void onInterrupted();

private:
    boost::asio::io_service* m_io_service;
    EmulatorConnectionManager::pointer m_manager;
    StreamServer* m_server;

    QString m_address;
    QString m_port;
    QString m_event_log_path;

    EXIT_RESULT m_exit_code;
};

#endif // SERVER_EMULATOR_H

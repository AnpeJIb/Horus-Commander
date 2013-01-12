#ifndef SERVER_EMULATOR_H
#define SERVER_EMULATOR_H

#include <QThread>
#include <QString>

#include "stream_server.h"
#include "emulator_connection_manager.h"
#include "console_prints_collector.h"
#include "event_file_logger.h"
#include "input_parser.h"

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
    void printToConsoleCalled(QString);

public slots:
    void processExternalInput(const QString& msg);

protected:
    void run();

private slots:
    void onStartFailure();
    void onStoppedNormally();
    void onInterrupted();

private:
    void connectParser();
    void connectServer();

    void printGreetings();

    boost::asio::io_service* m_io_service;
    EmulatorConnectionManager::pointer m_manager;
    StreamServer* m_server;
    ConsolePrintsCollector* m_console_prints_collector;
    EventFileLogger* m_event_file_logger;
    InputParser* m_input_parser;

    QString m_address;
    QString m_port;
    QString m_event_log_path;

    EXIT_RESULT m_exit_code;
};

#endif // SERVER_EMULATOR_H

#include "server_emulator.h"
#include "stream_defaults.h"

ServerEmulator::ServerEmulator()
    : m_address(StreamDefaults::default_address),
      m_port(StreamDefaults::default_port),
      m_event_log_path("./log"),
      m_exit_code(UNDEFINED)
{
}

void ServerEmulator::run()
{
    m_exit_code = UNDEFINED;
    m_io_service = new boost::asio::io_service;

    m_manager.reset(new EmulatorConnectionManager);
    m_input_parser = new InputParser;
    m_console_prints_collector = new ConsolePrintsCollector;
    m_event_file_logger = new EventFileLogger;
    m_event_file_logger->setup(m_event_log_path);

    connectParser();
    printGreetings();

    m_server = new StreamServer(m_address, m_port, *m_io_service, m_manager);
    connectServer();

    m_server->start();
    m_io_service->run();

    delete m_event_file_logger;
    delete m_console_prints_collector;
    delete m_input_parser;
    delete m_server;
    m_manager.reset();
    delete m_io_service;
}

void ServerEmulator::stop()
{
    m_server->stop();
}

void ServerEmulator::configure(const QString &address, const QString &port, const QString& event_log_path)
{
    m_address = address;
    m_port = port;
    m_event_log_path = event_log_path;
}

void ServerEmulator::onStartFailure()
{
    m_io_service->stop();
    m_exit_code = START_FAILED;
    emit startFailure();
}

void ServerEmulator::onStoppedNormally()
{
    m_io_service->stop();
    m_exit_code = STOPPED_NORMALLY;
    emit stoppedNormally();
}

void ServerEmulator::onInterrupted()
{
    m_io_service->stop();
    m_exit_code = INTERRUPTED;
    emit interrupted();
}

void ServerEmulator::connectParser()
{
    connect(m_console_prints_collector, SIGNAL(printToConsoleCalled(QString)),
            m_manager.get(), SLOT(sendMessage(const QString&)));

    connect(m_console_prints_collector, SIGNAL(printToConsoleCalled(QString)),
            this, SIGNAL(printToConsoleCalled(QString)));

    connect(m_manager.get(), SIGNAL(messageReceived(QString)),
            m_input_parser,  SLOT(parseString(const QString&)));
}

void ServerEmulator::connectServer()
{
    connect(m_server, SIGNAL(startSuccess()),
            this,     SIGNAL(startSuccess()), Qt::DirectConnection);

    connect(m_server, SIGNAL(startFailure()),
            this,     SLOT(onStartFailure()), Qt::DirectConnection);

    connect(m_server, SIGNAL(stoppedNormally()),
            this,     SLOT(onStoppedNormally()), Qt::DirectConnection);

    connect(m_server, SIGNAL(interrupted()),
            this,     SLOT(onInterrupted()), Qt::DirectConnection);
}

void ServerEmulator::printGreetings()
{
    emit printToConsoleCalled("IL-2 Horus Team: IL-2 FB dedicated server emulator");
    emit printToConsoleCalled("  *** Library **** DT ****  Loaded *** XXX");
    emit printToConsoleCalled("RTS Version Y.Y");
    emit printToConsoleCalled("Core Version Z.Z");
    emit printToConsoleCalled("Sound: Native library (build Q.Q, target - TTTT) loaded.");
    emit printToConsoleCalled("IL2 FB dedicated server vAA.BB.CC");
}

void ServerEmulator::processExternalInput(const QString &msg)
{
    m_input_parser->parseString(msg);
}

ServerEmulator::EXIT_RESULT ServerEmulator::exitResult()
{
    return (ServerEmulator::EXIT_RESULT) m_exit_code;
}

void ServerEmulator::userJoined(const QString &callsign, const QString &ip_address)
{
    int channel_number = m_pilot_manager.userJoined(callsign, ip_address);

    m_console_prints_collector->printToConsole(
                QString("socket channel '%1' start creating: ip %2:%3").arg(
                    QString::number(channel_number), ip_address, m_port));
    m_console_prints_collector->printToConsole(
                QString("Chat: --- %1 joins the game.").arg(callsign));
    m_console_prints_collector->printToConsole(
                QString("socket channel '%1', ip %2:%3, %4, is complete created.").arg(
                    QString::number(channel_number), ip_address, m_port, callsign));
}

void ServerEmulator::userLeft(const QString &callsign)
{
    // socketConnection with aaa.bbb.ccc.ddd:ppppp on channel N lost.  Reason: Remote user has left the game.
    // Chat: --- Callsign has left the game.
}

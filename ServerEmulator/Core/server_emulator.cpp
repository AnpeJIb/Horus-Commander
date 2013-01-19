#include "server_emulator.h"
#include "stream_defaults.h"

ServerEmulator::ServerEmulator()
    : m_address(StreamDefaults::default_address),
      m_stream_port(StreamDefaults::default_port),
      m_event_log_path("./log"),
      m_exit_code(UNDEFINED)
{
}

void ServerEmulator::run()
{
    init();
    printGreetings();
    m_input_parser->printPrompt();

    m_server = new StreamServer(m_address, m_stream_port, *m_io_service, m_connection_manager);
    connectServer();

    m_server->start();
    m_io_service->run();

    tearDown();
}

void ServerEmulator::init()
{
    m_exit_code = UNDEFINED;
    m_io_service = new boost::asio::io_service;

    m_connection_manager.reset(new EmulatorConnectionManager);
    m_console_prints_collector = new ConsolePrintsCollector;
    m_event_file_logger = new EventFileLogger;
    m_event_file_logger->setup(m_event_log_path);

    m_input_parser = new InputParser(m_console_prints_collector);
    m_pilot_manager = new PilotManager(m_stream_port, m_console_prints_collector);
    m_mission_manager = new MissionManager(m_console_prints_collector, m_event_file_logger);

    initConnections();
}

void ServerEmulator::initConnections()
{
    connect(m_console_prints_collector, SIGNAL(printToConsoleCalled(QString)),
            m_connection_manager.get(), SLOT(sendMessage(const QString&)), Qt::DirectConnection);

    connect(m_console_prints_collector, SIGNAL(printToConsoleCalled(QString)),
            this, SIGNAL(printToConsoleCalled(QString)), Qt::DirectConnection);

    connectParser();
}

void ServerEmulator::connectParser()
{
    connect(m_connection_manager.get(), SIGNAL(messageReceived(QString)),
            this,  SLOT(processMessageReceived(const QString&)), Qt::DirectConnection);

    connect(m_input_parser, SIGNAL(exitReq()),
            this, SLOT(stop()), Qt::DirectConnection);

    connect(m_input_parser, SIGNAL(serverInfoReq()),
            this, SLOT(onServerInfoReq()), Qt::DirectConnection);

    connectMissionManager();
}

void ServerEmulator::connectMissionManager()
{
    connect(m_input_parser,    SIGNAL(missionStatusReq()),
            m_mission_manager, SLOT(onMissionStatusReq()), Qt::DirectConnection);

    connect(m_input_parser,    SIGNAL(missionLoadReq(QString)),
            m_mission_manager, SLOT(onMissionLoadReq(const QString&)), Qt::DirectConnection);

    connect(m_input_parser,    SIGNAL(missionUnloadReq()),
            m_mission_manager, SLOT(onMissionUnloadReq()), Qt::DirectConnection);

    connect(m_input_parser,    SIGNAL(missionBeginReq()),
            m_mission_manager, SLOT(onMissionBeginReq()), Qt::DirectConnection);

    connect(m_input_parser,    SIGNAL(missionEndReq()),
            m_mission_manager, SLOT(onMissionEndReq()), Qt::DirectConnection);
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

void ServerEmulator::tearDown()
{
    delete m_pilot_manager;
    delete m_mission_manager;
    delete m_input_parser;

    delete m_event_file_logger;
    delete m_console_prints_collector;
    delete m_server;
    m_connection_manager.reset();
    delete m_io_service;
}

void ServerEmulator::stop()
{
    m_server->stop();
}

void ServerEmulator::configure(const QString &address, const QString &port, const QString& event_log_path)
{
    m_address = address;
    m_stream_port = port;
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

void ServerEmulator::onServerInfoReq()
{
    m_console_prints_collector->printToConsole("Type: Local server");
    m_console_prints_collector->printToConsole("Name: Server emulator");
    m_console_prints_collector->printToConsole("Description: Emulated IL-2 FB server with limited features" \
                                               "for IL-2 Horus Team purposes");
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

void ServerEmulator::processMessageReceived(const QString &msg)
{
    QString fixedMsg = msg;

    if (fixedMsg.endsWith('\n'))
        fixedMsg.remove(fixedMsg.length()-1, 1);
    if (fixedMsg.endsWith('\r'))
        fixedMsg.remove(fixedMsg.length()-1, 1);

    if (fixedMsg == "<QUIT QUIT>") return;

    emit printToConsoleCalled(fixedMsg);
    m_input_parser->parseString(fixedMsg);
}

void ServerEmulator::processExternalInput(const QString &msg)
{
    m_connection_manager->sendMessage(msg);
    m_input_parser->parseString(msg);
}

ServerEmulator::EXIT_RESULT ServerEmulator::exitResult()
{
    return (ServerEmulator::EXIT_RESULT) m_exit_code;
}

void ServerEmulator::pilotJoined(const QString &callsign, const QString &ip_address)
{
    m_pilot_manager->pilotJoined(callsign, ip_address);
}

void ServerEmulator::pilotLeft(const QString &callsign)
{
    m_pilot_manager->pilotLeft(callsign);
}

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
    m_server = new StreamServer(m_address, m_port, *m_io_service, m_manager);

    connect(m_server, SIGNAL(startSuccess()),
            this, SLOT(onStartSuccess()), Qt::DirectConnection);
    connect(m_server, SIGNAL(startFailure()),
            this, SLOT(onStartFailure()), Qt::DirectConnection);
    connect(m_server, SIGNAL(stoppedNormally()),
            this, SLOT(onStoppedNormally()), Qt::DirectConnection);
    connect(m_server, SIGNAL(interrupted()),
            this, SLOT(onInterrupted()), Qt::DirectConnection);

    m_server->start();
    m_io_service->run();

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

void ServerEmulator::onStartSuccess()
{
    // TODO:
    emit startSuccess();
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

ServerEmulator::EXIT_RESULT ServerEmulator::exitResult()
{
    return (ServerEmulator::EXIT_RESULT) m_exit_code;
}

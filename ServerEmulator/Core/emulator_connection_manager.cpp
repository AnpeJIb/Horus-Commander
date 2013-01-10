#include "emulator_connection_manager.h"

EmulatorConnectionManager::EmulatorConnectionManager()
{
    m_connection.reset();
}

void EmulatorConnectionManager::join(boost::shared_ptr<StreamServerConnection> connection)
{
    if (isNewConnectionAvailable() == false) return;

    m_connection = connection;

    connect(m_connection.get(), SIGNAL(messageReceived(QString)),
            this, SIGNAL(messageReceived(QString)));
    connect(this, SLOT(sendMessage(const QString& msg)),
            m_connection.get(), SLOT(sendMessage(const QString& msg)));

    m_connection->start();
    increaseConnections();
}

void EmulatorConnectionManager::leave(boost::shared_ptr<StreamServerConnection> connection)
{
    if (connection != m_connection) return;
    if (!m_connection) return;

    m_connection->stop();

    disconnect(m_connection.get(), SIGNAL(messageReceived(QString)),
               this, SIGNAL(messageReceived(QString)));
    disconnect(this, SLOT(sendMessage(const QString& msg)),
                m_connection.get(), SLOT(sendMessage(const QString& msg)));

    m_connection.reset();
    decreaseConnections();
}

void EmulatorConnectionManager::kickAll()
{
    leave(m_connection);
}

StreamServerConnection *EmulatorConnectionManager::getNewConnection(
        boost::asio::io_service &io_service,
        const boost::shared_ptr<StreamServerConnectionManager> &manager)
{
    return new StreamServerConnection(io_service, manager);
}

void EmulatorConnectionManager::setMaxConnections(uint value)
{
    Q_UNUSED(value);
}

#include "stream_server_connection_manager.h"

const uint c_max_connections = 1;

StreamServerConnectionManager::StreamServerConnectionManager()
    : m_max_connections(c_max_connections),
      m_current_connections(0)
{
}

StreamServerConnectionManager::StreamServerConnectionManager(uint max_connections)
    : m_max_connections(max_connections)
{
}

void StreamServerConnectionManager::setMaxConnections(uint value)
{
    m_max_connections = value;
}

bool StreamServerConnectionManager::isNewConnectionAvailable()
{
    return m_current_connections < m_max_connections;
}

void StreamServerConnectionManager::increaseConnections()
{
    m_current_connections++;
}

void StreamServerConnectionManager::decreaseConnections()
{
    m_current_connections--;
}

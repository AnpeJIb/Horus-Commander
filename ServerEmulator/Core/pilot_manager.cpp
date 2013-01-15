#include "pilot_manager.h"

PilotManager::PilotManager()
    : m_current_channel_number(-1)
{
}

int PilotManager::userJoined(const QString &callsign, const QString &ip_address)
{
    return newChannelNumber();
}

int PilotManager::newChannelNumber()
{
    m_current_channel_number += 2;
    return m_current_channel_number;
}

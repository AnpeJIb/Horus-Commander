#include "pilot_manager.h"

#include <QtCore>

PilotManager::PilotManager(const QString &server_stream_port, ConsolePrintsCollector *prints_collector)
    : m_server_stream_port(server_stream_port),
      m_prints_collector(prints_collector),
      m_current_channel_number(-1)
{
}

PilotManager::~PilotManager()
{
    foreach(pilot_info_t* p_inf, m_pilots_map.values())
    {
        delete p_inf;
    }
}

void PilotManager::pilotJoined(const QString &callsign, const QString &ip_address)
{
    uint pilotHash = qHash(callsign);
    pilot_info_t* p_inf = m_pilots_map[pilotHash];
    if (p_inf != NULL) return;

    p_inf = new pilot_info_t;
    p_inf->callsign = callsign;
    p_inf->ip_address = ip_address;
    p_inf->channel_number = newChannelNumber();
    m_pilots_map[pilotHash] = p_inf;

    m_prints_collector->printToConsole(QString("socket channel '%1' start creating: ip %2:%3").arg(
        QString::number(p_inf->channel_number),
        p_inf->ip_address,
        m_server_stream_port));

    m_prints_collector->printToConsole(QString("Chat: --- %1 joins the game.").arg(p_inf->callsign));

    m_prints_collector->printToConsole(QString("socket channel '%1', ip %2:%3, %4, is complete created.").arg(
        QString::number(p_inf->channel_number),
        p_inf->ip_address,
        m_server_stream_port,
        p_inf->callsign));
}

void PilotManager::pilotLeft(const QString &callsign)
{
    uint pilotHash = qHash(callsign);
    pilot_info_t* p_inf = m_pilots_map[pilotHash];
    if (p_inf == NULL) return;

    m_prints_collector->printToConsole(QString("socketConnection with %1:%2 on channel %3 lost." \
                                               "  Reason: Remote user has left the game.").arg(
        p_inf->ip_address,
        m_server_stream_port,
        QString::number(p_inf->channel_number)));

    m_prints_collector->printToConsole(QString("Chat: --- %1 has left the game.").arg(p_inf->callsign));

    m_pilots_map.remove(pilotHash);
    delete p_inf;
}

int PilotManager::newChannelNumber()
{
    m_current_channel_number += 2;
    return m_current_channel_number;
}

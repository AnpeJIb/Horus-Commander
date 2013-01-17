#include "mission_manager.h"

#include <QtCore>

MissionManager::MissionManager(ConsolePrintsCollector *prints_collector, EventFileLogger *file_logger)
    : m_prints_collector(prints_collector),
      m_file_logger(file_logger),
      m_mission_path("no path"),
      m_status(MISSION_NOT_LOADED)
{
}

void MissionManager::onMissionStatusReq()
{
    switch (m_status)
    {
        case MISSION_NOT_LOADED:
            m_prints_collector->printToConsole("Mission NOT loaded\n");
            break;
        case MISSION_LOADED:
            m_prints_collector->printToConsole(QString("Mission: %1 is Loaded\n").arg(m_mission_path));
            break;
        case MISSION_PLAYING:
            m_prints_collector->printToConsole(QString("Mission: %1 is Playing\n").arg(m_mission_path));
            break;
        default:
            break;
    }
}

void MissionManager::onMissionLoadReq(const QString &mission_path)
{
    if (m_status != MISSION_NOT_LOADED) return;

    m_mission_path = mission_path;

    m_prints_collector->printToConsole(QString("Loading mission %1...\n").arg(m_mission_path));
    m_prints_collector->printToConsole("Load bridges\n");
    m_prints_collector->printToConsole("Load static objects\n");
    m_prints_collector->printToConsole("##### House without collision (3do/Tree/Tree2.sim)\n");
    m_prints_collector->printToConsole("##### House without collision (3do/Buildings/Port/Floor/live.sim)\n");
    m_prints_collector->printToConsole("##### House without collision (3do/Buildings/Port/BaseSegment/live.sim)\n");
    m_prints_collector->printToConsole(QString("Mission: %1 is Loaded\n").arg(m_mission_path));

    m_status = MISSION_LOADED;
}

void MissionManager::onMissionBeginReq()
{
    if (m_status != MISSION_LOADED) return;

    m_prints_collector->printToConsole(QString("Mission: %1 is Playing\n").arg(m_mission_path));
    m_file_logger->logEvent(QString("Mission: %1 is Playing").arg(m_mission_path), true);
    m_file_logger->logEvent("Mission BEGIN");

    m_status = MISSION_PLAYING;
}

void MissionManager::onMissionEndReq()
{
    if (m_status != MISSION_PLAYING) return;

    m_file_logger->logEvent("Mission END");
    m_status = MISSION_LOADED;
}

void MissionManager::onMissionUnloadReq()
{
    if (m_status == MISSION_NOT_LOADED) return;
    if (m_status == MISSION_PLAYING) onMissionEndReq();
    m_status = MISSION_NOT_LOADED;
}

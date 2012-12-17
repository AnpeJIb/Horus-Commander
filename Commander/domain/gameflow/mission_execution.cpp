#include "mission_execution.h"

using namespace Domain::Gameflow;

MissionExecution::MissionExecution()
{
}

MissionExecution::~MissionExecution()
{
}

Domain::Belligerent *MissionExecution::belligerent()
{
    return m_belligerent;
}

Battleground *MissionExecution::battleground()
{
    return m_battleground;
}

WeatherReport *MissionExecution::weatherReport()
{
    return m_weatherReport;
}

MissionCycle *MissionExecution::missionCycle()
{
    return m_missionCycle;
}

MissionDefinition *MissionExecution::missionDefinition()
{
    return m_missionDefinition;
}

Domain::CommanderInfo *MissionExecution::commanderInfo()
{
    return m_commanderInfo;
}

void MissionExecution::setBelligerent(Domain::Belligerent *value)
{
    m_belligerent = value;
}

void MissionExecution::setBattleground(Battleground *value)
{
    m_battleground = value;
}

void MissionExecution::setWeatherReport(WeatherReport *value)
{
    m_weatherReport = value;
}

void MissionExecution::setMissionCycle(MissionCycle *value)
{
    m_missionCycle = value;
}

void MissionExecution::missionDefinition(MissionDefinition *value)
{
    m_missionDefinition = value;
}

void MissionExecution::setCommanderInfo(Domain::CommanderInfo *value)
{
    m_commanderInfo = value;
}

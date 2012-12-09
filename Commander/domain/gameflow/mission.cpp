#include "mission.h"

using namespace Domain::Gameflow;

Battleground *Mission::battleground()
{
    // TODO: NULL-CHECK
    return m_battleground;
}

WeatherReport *Mission::weatherReport()
{
    // TODO: NULL-CHECK
    return m_weatherReport;
}

MissionsCycle *Mission::cycle()
{
    // TODO: NULL-CHECK
    return m_cycle;
}

ServerCommanderD *Mission::commander()
{
    // TODO: NULL-CHECK
    return m_commander;
}

void Mission::setBattleground(Battleground *value)
{
    // TODO: NULL-CHECK
    m_battleground = value;
}

void Mission::setWeatherReport(WeatherReport *value)
{
    // TODO: NULL-CHECK
    m_weatherReport = value;
}

void Mission::setCycle(MissionsCycle *value)
{
    // TODO: NULL-CHECK
    m_cycle = value;
}

void Mission::setCommander(ServerCommanderD *value)
{
    // TODO: NULL-CHECK
    m_commander = value;
}

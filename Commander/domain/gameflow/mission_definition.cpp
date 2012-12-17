#include "mission_definition.h"

using namespace Domain::Gameflow;

MissionDefinition::MissionDefinition()
{
}

MissionDefinition::~MissionDefinition()
{
}

Battleground *MissionDefinition::battleground()
{
    return m_battleground;
}

Scheme *MissionDefinition::scheme()
{
    return m_scheme;
}

MissionSet *MissionDefinition::missionSet()
{
    return m_missionSet;
}

MissionDefinition *MissionDefinition::nextNone()
{
    return m_nextNone;
}

MissionDefinition *MissionDefinition::nextRed()
{
    return m_nextRed;
}

MissionDefinition *MissionDefinition::nextBlue()
{
    return m_nextBlue;
}

void MissionDefinition::setBattleground(Battleground *value)
{
    m_battleground = value;
}

void MissionDefinition::setScheme(Scheme *value)
{
    m_scheme = value;
}

void MissionDefinition::setMissionSet(MissionSet *value)
{
    m_missionSet = value;
}

void MissionDefinition::setNextNone(MissionDefinition *value)
{
    m_nextNone = value;
}

void MissionDefinition::setNextRed(MissionDefinition *value)
{
    m_nextRed = value;
}

void MissionDefinition::setNextBlue(MissionDefinition *value)
{
    m_nextRed = value;
}

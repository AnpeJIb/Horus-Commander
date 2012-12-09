#include "mission_set_element.h"

using namespace Domain::Gameflow;

Mission* MissionSetElement::mission()
{
    // TODO: NULL-CHECK
    return m_mission;
}

void MissionSetElement::setMission(Mission *value)
{
    // TODO: NULL-CHECK
    m_mission = value;
}

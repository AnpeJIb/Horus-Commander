#include "missions_cycle.h"

Domain::Belligerent *Domain::Gameflow::MissionsCycle::winner()
{
    // TODO: NULL-CHECK
    return m_winner;
}

void Domain::Gameflow::MissionsCycle::setWinner(Domain::Belligerent *value)
{
    // TODO: NULL-CHECK
    m_winner = value;
}

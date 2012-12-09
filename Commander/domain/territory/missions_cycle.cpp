#include "missions_cycle.h"

Domain::Belligerent *Domain::Territory::MissionsCycle::winner()
{
    // TODO: NULL-CHECK
    return m_winner;
}

void Domain::Territory::MissionsCycle::setWinner(Domain::Belligerent *value)
{
    // TODO: NULL-CHECK
    m_winner = value;
}

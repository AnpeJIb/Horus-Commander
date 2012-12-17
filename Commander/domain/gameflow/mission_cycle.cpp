#include "mission_cycle.h"

using namespace Domain::Gameflow;

MissionCycle::MissionCycle()
{
}

MissionCycle::~MissionCycle()
{
}

Domain::Belligerent *MissionCycle::belligerent()
{
    return m_belligerent;
}

void MissionCycle::setBelligerent(Domain::Belligerent *value)
{
    m_belligerent = value;
}

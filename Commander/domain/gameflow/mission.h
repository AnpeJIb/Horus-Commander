#ifndef MISSION_H
#define MISSION_H

#include <QString>

#include "generic_domain.h"
#include "battleground.h"
#include "weather_report.h"
#include "missions_cycle.h"

namespace Domain { namespace Gameflow {

using namespace Territory;

class Mission: public GenericDomain
{
public:
    enum MissionState
    {
        MISSION_PLAYING     = 0,
        MISSION_FINISHED    = 1,
        MISSION_INTERRUPTED = 2
    };

    Mission();

    QString filePath;
    quint8 state;

private:
    Battleground* m_battleground;
    WeatherReport* m_weatherReport;
    MissionsCycle* m_cycle;
};

}}

#endif // MISSION_H

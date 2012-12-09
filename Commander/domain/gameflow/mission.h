#ifndef MISSION_H
#define MISSION_H

#include <QString>

#include "generic_domain.h"
#include "battleground.h"
#include "weather_report.h"
#include "missions_cycle.h"
#include "d_server_commander.h"

namespace Domain { namespace Gameflow {

using namespace Territory;
using namespace Domain::ServerCommander;

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

    Battleground* battleground();
    WeatherReport* weatherReport();
    MissionsCycle* cycle();
    ServerCommanderD* commander();

    void setBattleground(Battleground* value);
    void setWeatherReport(WeatherReport* value);
    void setCycle(MissionsCycle* value);
    void setCommander(ServerCommanderD* value);

private:
    Battleground* m_battleground;
    WeatherReport* m_weatherReport;
    MissionsCycle* m_cycle;
    ServerCommanderD* m_commander;
};

}}

#endif // MISSION_H

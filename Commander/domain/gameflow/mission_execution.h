#ifndef MISSION_EXECUTION_H
#define MISSION_EXECUTION_H

#include <QString>
#include <QDateTime>

#include "mission_cycle.h"
#include "weather_report.h"
#include "mission_definition.h"
#include "belligerent_carrier.h"
#include "battleground_carrier.h"
#include "commander_info.h"
#include "generic_domain.h"

namespace Domain { namespace Gameflow {

class MissionExecution: public GenericDomain, public BelligerentCarrier, public BattlegroundCarrier
{
public:
    enum MissionState
    {
        MISSION_PLAYING     = 0,
        MISSION_FINISHED    = 1,
        MISSION_INTERRUPTED = 2
    };

    MissionExecution();
    ~MissionExecution();

    Belligerent* belligerent();
    Battleground* battleground();
    WeatherReport* weatherReport();
    MissionCycle* missionCycle();
    MissionDefinition* missionDefinition();
    CommanderInfo* commanderInfo();

    void setBelligerent(Belligerent* value);
    void setBattleground(Battleground* value);
    void setWeatherReport(WeatherReport* value);
    void setMissionCycle(MissionCycle* value);
    void missionDefinition(MissionDefinition* value);
    void setCommanderInfo(CommanderInfo* value);

    quint8 state;
    QString filePath;
    QDateTime startTD;
    QDateTime stopTD;

private:
    MissionCycle* m_missionCycle;
    WeatherReport* m_weatherReport;
    MissionDefinition* m_missionDefinition;
    CommanderInfo* m_commanderInfo;
};

}}

#endif // MISSION_EXECUTION_H

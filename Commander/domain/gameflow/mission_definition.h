#ifndef MISSION_DEFINITION_H
#define MISSION_DEFINITION_H

#include <QString>

#include "generic_domain.h"
#include "kind_carrier.h"
#include "battleground_carrier.h"
#include "scheme_carrier.h"
#include "mission_set.h"

namespace Domain { namespace Gameflow {

using namespace Territory;
using namespace Parameters;

class MissionDefinition;

class MissionDefinition: public GenericDomain, public KindCarrier,
        public BattlegroundCarrier, public SchemeCarrier
{
public:
    enum CyclePointType
    {
        CYCLE_POINT_START   = 0,
        CYCLE_POIN_STOP     = 1,
        CYCLE_POINT_NORMAL  = 2
    };

    enum MissionLoadAlgorithm
    {
        MISSION_LOAD_STATIC     = 0,
        MISSION_LOAD_DYNAMIC    = 1,
        MISSION_LOAD_STRICT     = 2,
        MISSION_LOAD_SOFT_FULL  = 3,
        MISSION_LOAD_SOFT_NEAR  = 4
    };

    MissionDefinition();
    ~MissionDefinition();

    Battleground* battleground();
    Scheme* scheme();
    MissionSet* missionSet();
    MissionDefinition* nextNone();
    MissionDefinition* nextRed();
    MissionDefinition* nextBlue();

    void setBattleground(Battleground* value);
    void setScheme(Scheme* value);
    void setMissionSet(MissionSet* value);
    void setNextNone(MissionDefinition* value);
    void setNextRed(MissionDefinition* value);
    void setNextBlue(MissionDefinition* value);

    uint duration;
    bool isCurrent;
    QString parameter;
    quint8 loadAlgorithm;

private:
    MissionSet* m_missionSet;
    MissionDefinition* m_nextNone;
    MissionDefinition* m_nextRed;
    MissionDefinition* m_nextBlue;
};

}}

#endif // MISSION_DEFINITION_H

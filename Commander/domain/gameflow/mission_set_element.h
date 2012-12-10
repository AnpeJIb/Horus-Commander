#ifndef MISSION_SET_ELEMENT_H
#define MISSION_SET_ELEMENT_H

#include <QString>

#include "generic_domain.h"
#include "titled_domain.h"
#include "type_carrier.h"
#include "mission.h"

namespace Domain { namespace Gameflow {

class MissionSetElement: public GenericDomain, public TitledDomain, public TypeCarrier
{
public:
    enum CyclePointType
    {
        CYCLE_POINT_START   = 0,
        CYCLE_POIN_STOP     = 1,
        CYCLE_POINT_NORMAL  = 2
    };

    enum MissionLoadingAlgorithm
    {
        MISSION_LOAD_STATIC     = 0,
        MISSION_LOAD_DYNAMIC    = 1,
        MISSION_LOAD_STRICT     = 2,
        MISSION_LOAD_SOFT_FULL  = 3,
        MISSION_LOAD_SOFT_NEAR  = 4
    };

    enum MissionFinishingAlgorithm
    {
        MISSION_DESTROY_TARGETS = 0,
        MISSION_CAPTURE_MAP     = 1
    };

    MissionSetElement();

    QString parameter;

    bool isCurrent;

    QString nextNone;
    QString nextRed;
    QString nextBlue;

    quint8 loadingAlgorithm;
    quint8 finishingAlgorithm;

    Mission* mission();
    void setMission(Mission* value);

private:
    Mission* m_mission;
};

}}

#endif // MISSION_SET_ELEMENT_H

#ifndef MISSION_CYCLE_H
#define MISSION_CYCLE_H

#include <QDateTime>

#include "belligerent_carrier.h"
#include "type_carrier.h"
#include "generic_domain.h"
#include "bitwise.h"

namespace Domain { namespace Gameflow {

class MissionCycle: public GenericDomain, public TypeCarrier, BelligerentCarrier
{
public:
    enum CycleType
    {
        CYCLE_WAR       = 0,
        CYCLE_TRAINING  = 1
    };

    MissionCycle();
    ~MissionCycle();

    bool isWar(){return BIT_CHECK(type, CYCLE_WAR);}
    bool isTraining(){return BIT_CHECK(type, CYCLE_TRAINING);}
    /** Get winner */
    Belligerent* belligerent();

    void setWar(bool value){BIT_SET(type, CYCLE_WAR, value);}
    void setTraining(bool value){BIT_SET(type, CYCLE_TRAINING, value);}
    /** Set winner */
    void setBelligerent(Belligerent* value);

    QDateTime startRealTD;
    QDateTime startGameTD;
    QDateTime stopRealTD;
    QDateTime stopGameTD;
};

}}

#endif // MISSION_CYCLE_H

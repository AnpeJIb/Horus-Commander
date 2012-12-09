#ifndef MISSIONS_CYCLE_H
#define MISSIONS_CYCLE_H

#include <QDateTime>

#include "belligerent.h"
#include "generic_domain.h"
#include "type_carrier.h"
#include "bitwise.h"

namespace Domain { namespace Gameflow {

class MissionsCycle: public GenericDomain, public TypeCarrier
{
public:
    enum CycleType
    {
        CYCLE_WAR       = 0,
        CYCLE_TRAINING  = 1
    };

    MissionsCycle();

    QDateTime startRealTD;
    QDateTime startGameTD;
    QDateTime stopRealTD;
    QDateTime stopGameTD;

    bool isWar(){return BIT_CHECK(type, CYCLE_WAR);}
    bool isTraining(){return BIT_CHECK(type, CYCLE_TRAINING);}

    void setWar(bool value){BIT_SET(type, CYCLE_WAR, value);}
    void setTraining(bool value){BIT_SET(type, CYCLE_TRAINING, value);}

    Belligerent* winner();
    void setWinner(Belligerent* value);

private:
    Belligerent* m_winner;
};

}}

#endif // MISSIONS_CYCLE_H

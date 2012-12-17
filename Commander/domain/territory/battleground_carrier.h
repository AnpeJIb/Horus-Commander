#ifndef BATTLEGROUND_CARRIER_H
#define BATTLEGROUND_CARRIER_H

#include "battleground.h"

namespace Domain { namespace Territory {

class BattlegroundCarrier
{
public:
    virtual Battleground* battleground() = 0;
    virtual void setBattleground(Battleground* value) = 0;

protected:
    Battleground* m_battleground;
};

}}

#endif // BATTLEGROUND_CARRIER_H

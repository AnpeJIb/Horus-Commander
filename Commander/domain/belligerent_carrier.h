#ifndef BELLIGERENT_CARRIER_H
#define BELLIGERENT_CARRIER_H

#include "belligerent.h"

namespace Domain {

class BelligerentCarrier
{
public:
    virtual Belligerent* belligerent() = 0;
    virtual void setBelligerent(Belligerent* value) = 0;

protected:
    Belligerent* m_belligerent;
};

}

#endif // BELLIGERENT_CARRIER_H

#ifndef KIND_CARRIER_H
#define KIND_CARRIER_H

#include <QtCore>

namespace Domain {

class KindCarrier
{
public:
    virtual ~KindCarrier() = 0;

    uint kind;
};

inline KindCarrier::~KindCarrier(){}

}

#endif // KIND_CARRIER_H

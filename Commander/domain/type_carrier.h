#ifndef TYPE_CARRIER_H
#define TYPE_CARRIER_H

#include <QtCore>

namespace Domain {

class TypeCarrier
{
public:
    virtual ~TypeCarrier() = 0;

    uint type;
};

inline TypeCarrier::~TypeCarrier(){}

}

#endif // TYPE_CARRIER_H

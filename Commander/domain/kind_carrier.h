#ifndef KIND_CARRIER_H
#define KIND_CARRIER_H

#include <QtCore>

typedef uint domain_kind_t;

namespace Domain {

class KindCarrier
{
public:
    virtual ~KindCarrier() = 0;

    domain_kind_t kind;
};

inline KindCarrier::~KindCarrier(){}

}

#endif // KIND_CARRIER_H

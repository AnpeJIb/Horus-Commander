#ifndef KIND_CARRIER_H
#define KIND_CARRIER_H

#include <QtCore>

typedef uint domain_kind_t;

namespace Domain {

class KindCarrier
{
public:
    KindCarrier(){}
    KindCarrier(domain_kind_t value) : kind(value) {}

    virtual ~KindCarrier() = 0;

    domain_kind_t kind;
};

inline KindCarrier::~KindCarrier(){}

}

#endif // KIND_CARRIER_H

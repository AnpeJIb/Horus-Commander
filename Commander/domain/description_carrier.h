#ifndef DESCRIPTION_CARRIER_H
#define DESCRIPTION_CARRIER_H

#include <QString>

typedef QString domain_descr_t;

namespace Domain {

class DescriptionCarrier
{
public:
    virtual ~DescriptionCarrier() = 0;

    domain_descr_t description;
};

inline DescriptionCarrier::~DescriptionCarrier(){}

}

#endif // DESCRIPTION_CARRIER_H

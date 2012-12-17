#ifndef DESCRIPTION_CARRIER_H
#define DESCRIPTION_CARRIER_H

#include <QString>

namespace Domain {

class DescriptionCarrier
{
public:
    virtual ~DescriptionCarrier() = 0;

    QString description;
};

inline DescriptionCarrier::~DescriptionCarrier(){}

}

#endif // DESCRIPTION_CARRIER_H

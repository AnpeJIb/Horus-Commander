#ifndef GENERIC_DOMAIN_H
#define GENERIC_DOMAIN_H

#include <QtCore>

namespace Domain {

class GenericDomain
{
public:
    virtual ~GenericDomain() = 0;

    qlonglong id;
};

inline GenericDomain::~GenericDomain(){}

}

#endif // GENERIC_DOMAIN_H

#ifndef GENERIC_DOMAIN_H
#define GENERIC_DOMAIN_H

#include <QtCore>

typedef quint64 domain_id_t;

namespace Domain {

class GenericDomain
{
public:
    virtual ~GenericDomain() = 0;

    domain_id_t id;
};

inline GenericDomain::~GenericDomain(){}

}

#endif // GENERIC_DOMAIN_H

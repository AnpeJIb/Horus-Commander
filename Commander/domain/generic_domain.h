#ifndef GENERIC_DOMAIN_H
#define GENERIC_DOMAIN_H

#include <QtCore>

typedef qulonglong domain_id_t;

namespace Domain {

class GenericDomain
{
public:
    GenericDomain():id(Q_UINT64_C(0)){}
    virtual ~GenericDomain() = 0;

    domain_id_t id;
};

inline GenericDomain::~GenericDomain(){}

}

#endif // GENERIC_DOMAIN_H

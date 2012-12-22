#ifndef GENERIC_DAO_H
#define GENERIC_DAO_H

#include "generic_domain.h"

namespace Dao {

template <class T> class GenericDao
{
public:
    /** Save new domain object to data source and get id */
    virtual void save(T* domain) = 0;

    /** Find domain object by id in data source */
    virtual bool find(domain_id_t id, T* result) = 0;

    /** Update domain object existing in data source */
    virtual void update(const T& domain) = 0;

    /** Remove existing domain object from data source */
    virtual void remove(const T& domain) = 0;
};

}

#endif // GENERIC_DAO_H
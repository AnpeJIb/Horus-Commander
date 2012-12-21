#ifndef GENERIC_DAO_H
#define GENERIC_DAO_H

#include "generic_domain.h"

namespace Dao {

template <class T> class GenericDao
{
public:
    /** Save new domain object to data source and get id */
    virtual domain_id_t save(T* domain) = 0;

    /** Find domain object by id in data source */
    virtual T* find(domain_id_t id) = 0;

    /** Update domain object existing in data source */
    virtual void update(T* domain) = 0;

    /** Remove existing domain object from data source */
    virtual void remove(T* domain) = 0;
};

}

#endif // GENERIC_DAO_H

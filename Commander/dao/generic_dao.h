#ifndef GENERIC_DAO_H
#define GENERIC_DAO_H

#include "generic_domain.h"

#include <QMap>
#include <QList>

namespace Dao {

template <class T> class GenericDao
{
public:

    /** Save new domain object to data source and get id */
    virtual void save(T* domain) = 0;

    /** Get all existing domain objects */
    virtual void all(QList<T *> *result) = 0;

    /** Find domain object by id in data source */
    virtual T* find(domain_id_t id) = 0;

    /** Update domain object existing in data source */
    virtual void update(T* domain) = 0;

    /** Remove existing domain object from data source */
    virtual void remove(T* domain) = 0;

    static void cachePut(T* domain)
    {
        cache[domain->id] = domain;
    }

    static T* cacheGet(domain_id_t id)
    {
        return cache[id];
    }

    static void cacheRemoveAndDispose(domain_id_t id)
    {
        T* cached = cache[id];
        if (cached != NULL)
        {
            cache.remove(id);
            delete cached;
        }
    }

    static void clearCache()
    {
        cache.clear();
    }

    static void clearCacheAndDisposeDomains()
    {
        QList< T* > lst = cache.values();

        foreach (T* domain, lst)
            delete domain;

        clearCache();
    }

private:
    static QMap<domain_id_t, T*> cache;
};

template <class T> QMap<domain_id_t, T*> GenericDao<T>::cache;

}

#endif // GENERIC_DAO_H

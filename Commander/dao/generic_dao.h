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
    virtual void update(const T* domain) = 0;

    /** Remove existing domain object from data source */
    virtual void remove(const T* domain) = 0;

    static void clearCache();
    static void clearCacheAndDisposeDomains();

protected:
    static QMap<domain_id_t, T*> cache;
};

template <class T> QMap<domain_id_t, T*> GenericDao<T>::cache;

template <class T> void GenericDao<T>::clearCache()
{
    cache.clear();
}

template <class T> void GenericDao<T>::clearCacheAndDisposeDomains()
{
    QList< T* > lst = cache.values();

    clearCache();

    foreach (T* domain, lst)
        delete domain;
}

}

#endif // GENERIC_DAO_H

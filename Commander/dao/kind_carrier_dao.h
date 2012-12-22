#ifndef KIND_CARRIER_DAO_H
#define KIND_CARRIER_DAO_H

#include "kind_carrier.h"
#include <QList>

namespace Dao {

template <class T> class KindCarrierDao
{
public:
    /** Find domain object in data source by kind */
    virtual void findByKind(domain_kind_t kind, QList< T* >* result) = 0;
};

}

#endif // KIND_CARRIER_DAO_H

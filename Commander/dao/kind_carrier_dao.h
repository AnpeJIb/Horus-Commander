#ifndef KIND_CARRIER_DAO_H
#define KIND_CARRIER_DAO_H

#include "kind_carrier.h"

namespace Dao {

template <class T> class KindCarrierDao
{
public:
    /** Find domain object in data source by kind */
    virtual T* findByKind(const domain_kind_t& value) = 0;
};

}

#endif // KIND_CARRIER_DAO_H

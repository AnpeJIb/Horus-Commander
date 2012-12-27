#ifndef DESCRIPTION_CARRIER_DAO_H
#define DESCRIPTION_CARRIER_DAO_H

#include "description_carrier.h"
#include <QList>

namespace Dao {

template <class T> class DescriptionCarrierDao
{
public:
    /** Find domain objects in data source by description */
    virtual void findByDescription(const domain_descr_t& descr, QList< T* >* result) = 0;
};

}

#endif // DESCRIPTION_CARRIER_DAO_H

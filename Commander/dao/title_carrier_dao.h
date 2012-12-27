#ifndef TITLE_CARRIER_DAO_H
#define TITLE_CARRIER_DAO_H

#include "title_carrier.h"
#include <QList>

namespace Dao {

template <class T> class TitleCarrierDao
{
public:
    /** Find domain objects in data source by title */
    virtual void findByTitle(const domain_title_t& title, QList< T* >* result) = 0;
};

}

#endif // TITLE_CARRIER_DAO_H

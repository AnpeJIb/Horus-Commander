#ifndef TITLE_CARRIER_DAO_H
#define TITLE_CARRIER_DAO_H

#include "title_carrier.h"

namespace Dao {

template <class T> class TitleCarrierDao
{
public:
    /** Find domain object in data source by title */
    virtual T* findByTitle(const domain_title_t& value) = 0;
};

}

#endif // TITLE_CARRIER_DAO_H

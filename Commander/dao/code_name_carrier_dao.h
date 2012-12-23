#ifndef CODE_NAME_CARRIER_DAO_H
#define CODE_NAME_CARRIER_DAO_H

#include "code_name_carrier.h"
#include <QList>

namespace Dao {

template <class T> class CodeNameCarrierDao
{
public:
    /** Find domain object in data source by code name */
    virtual void findByCodeName(domain_codeName_t codeName, QList< T* >* result) = 0;
};

}


#endif // CODE_NAME_CARRIER_DAO_H

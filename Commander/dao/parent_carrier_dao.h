#ifndef PARENT_CARRIER_DAO_H
#define PARENT_CARRIER_DAO_H

#include <QList>

namespace Dao {

template <class T> class ParentCarrierDao
{
public:
    /** Find domain object in data source by its parent */
    virtual void findByParent(const T* parent, QList< T* >* result) = 0;
};

}

#endif // PARENT_CARRIER_DAO_H

#ifndef SCHEME_CARRIER_DAO_H
#define SCHEME_CARRIER_DAO_H

#include "scheme.h"
#include <QList>

using namespace Domain::Parameters;

namespace Dao { namespace Parameters {

template <class T> class SchemeCarrierDao
{
public:
    /** Find domain objects in data source by parameter scheme */
    virtual void findByScheme(const Scheme* scheme, QList< T* >* result) = 0;
};

}}

#endif // SCHEME_CARRIER_DAO_H

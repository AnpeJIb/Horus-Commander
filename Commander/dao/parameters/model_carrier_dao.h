#ifndef MODEL_CARRIER_DAO_H
#define MODEL_CARRIER_DAO_H

#include "title_carrier.h"
#include "model.h"
#include <QList>

using namespace Domain::Parameters;

namespace Dao { namespace Parameters {

template <class T> class ModelCarrierDao
{
public:
    /** Find domain object in data source by parameter model */
    virtual void findByModel(const Model* model, QList< T* >* result) = 0;
};

}}

#endif // MODEL_CARRIER_DAO_H
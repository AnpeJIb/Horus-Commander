#ifndef MODEL_DAO_H
#define MODEL_DAO_H

#include "generic_dao.h"
#include "title_carrier_dao.h"
#include "kind_carrier_dao.h"
#include "model.h"

using namespace Domain::Parameters;

namespace Dao { namespace Parameters {

class ModelDao: public GenericDao<Model>, public TitleCarrierDao<Model>, public KindCarrierDao<Model>
{
public:
};

}}

#endif // MODEL_DAO_H

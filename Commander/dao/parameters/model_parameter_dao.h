#ifndef MODEL_PARAMETER_DAO_H
#define MODEL_PARAMETER_DAO_H

#include "generic_dao.h"
#include "model_parameter.h"
#include "model_parameter_helper.h"

#include "title_carrier_dao.h"
#include "kind_carrier_dao.h"
#include "model_carrier_dao.h"
#include "parent_carrier_dao.h"

using namespace Domain::Parameters;

namespace Dao { namespace Parameters {

class ModelParameterDao:
        public GenericDao<ModelParameter>,
        public TitleCarrierDao<ModelParameter>,
        public KindCarrierDao<ModelParameter>,
        public ModelCarrierDao<ModelParameter>,
        public ParentCarrierDao<ModelParameter>,
        public ModelParameterHelper
{
public:
    /** Find domain objects in data source by simple paramter */
    virtual void findBySimpleParameter(const SimpleParameter* parameter, QList< ModelParameter* >* result) = 0;
};

}}

#endif // MODEL_PARAMETER_DAO_H

#ifndef PARAMETER_DAO_H
#define PARAMETER_DAO_H

#include "generic_dao.h"
#include "title_carrier_dao.h"
#include "kind_carrier_dao.h"
#include "code_name_carrier_dao.h"
#include "parent_carrier_dao.h"
#include "model_parameter.h"

using namespace Domain::Parameters;

namespace Dao { namespace Parameters {

class ModelParameterDao:
        public GenericDao<ModelParameter>,
        public TitleCarrierDao<ModelParameter>,
        public KindCarrierDao<ModelParameter>,
        public CodeNameCarrierDao<ModelParameter>,
        public ParentCarrierDao<ModelParameter>
{
public:
    /** Find parameter in data source by model */
    virtual void findByModel(const Model* model, QList< ModelParameter* >* result) = 0;
};

}}

#endif // PARAMETER_DAO_H

#ifndef MODEL_PARAMETER_VALUE_DAO_H
#define MODEL_PARAMETER_VALUE_DAO_H

#include "generic_dao.h"
#include "model_parameter_value.h"
#include "model_parameter_value_helper.h"

#include "scheme_carrier_dao.h"

using namespace Domain::Parameters;

namespace Dao { namespace Parameters {

class ModelParameterValueDao:
        public GenericDao<ModelParameterValue>,
        public SchemeCarrierDao<ModelParameterValue>,
        public ModelParameterValueHelper
{
public:
    /** Find domain objects in data source by model parameter */
    virtual void findByModelParameter(const ModelParameter* parameter, QList< ModelParameterValue* >* result) = 0;

    /** Find domain objects in data source by value */
    virtual void findByValue(const QString& value, QList< ModelParameterValue* >* result) = 0;

    /** Find domain objects in data source by simple paramter codename for model scheme */
    virtual void findByCodeNameForScheme(
            const domain_codeName_t& codemane, const Scheme* scheme, QList< ModelParameterValue* >* result) = 0;
};

}}


#endif // MODEL_PARAMETER_VALUE_DAO_H

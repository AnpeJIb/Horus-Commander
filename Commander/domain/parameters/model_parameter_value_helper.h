#ifndef MODEL_PARAMETER_VALUE_HELPER_H
#define MODEL_PARAMETER_VALUE_HELPER_H

#include "model_parameter_value.h"
#include "domain_helper.h"

namespace Domain { namespace Parameters {

class ModelParameterValue;
class ModelParameterValueHelper;

class ModelParameterValueHelper: public DomainHelper<ModelParameterValueHelper>
{
public:
    virtual void loadScheme(ModelParameterValue* domain) = 0;
    virtual void loadModelParameter(ModelParameterValue* domain) = 0;
};

}}

#endif // MODEL_PARAMETER_VALUE_HELPER_H

#ifndef MODEL_PARAMETER_HELPER_H
#define MODEL_PARAMETER_HELPER_H

#include "model_parameter.h"
#include "domain_helper.h"

namespace Domain { namespace Parameters {

class ModelParameter;
class ModelParameterHelper;

class ModelParameterHelper: public DomainHelper<ModelParameterHelper>
{
public:
    virtual void loadParent(ModelParameter* domain) = 0;
    virtual void loadModel(ModelParameter* domain) = 0;
    virtual void loadSimpleParameter(ModelParameter* domain) = 0;
};

}}

#endif // MODEL_PARAMETER_HELPER_H

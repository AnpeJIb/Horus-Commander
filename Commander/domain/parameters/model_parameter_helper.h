#ifndef MODEL_PARAMETER_HELPER_H
#define MODEL_PARAMETER_HELPER_H

#include "model_parameter.h"

namespace Domain { namespace Parameters {

class ModelParameter;

class ModelParameterHelper
{
public:
    virtual void loadParent(ModelParameter* domain) = 0;
    virtual void loadModel(ModelParameter* domain) = 0;
    virtual void loadSimpleParameter(ModelParameter* domain) = 0;
};

}}

#endif // MODEL_PARAMETER_HELPER_H

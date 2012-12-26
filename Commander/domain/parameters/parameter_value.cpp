#include "model_parameter_value.h"

using namespace Domain;
using namespace Domain::Parameters;

ModelParameterValue::ModelParameterValue()
{
}

ModelParameterValue::~ModelParameterValue()
{
}

Scheme *ModelParameterValue::scheme()
{
    return m_scheme;
}

ModelParameter *ModelParameterValue::parameter()
{
    return m_parameter;
}

void ModelParameterValue::setScheme(Scheme *value)
{
    m_scheme = value;
}

void ModelParameterValue::setParameter(ModelParameter *value)
{
    m_parameter = value;
}

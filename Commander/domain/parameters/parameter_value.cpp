#include "parameter_value.h"

using namespace Domain;
using namespace Domain::Parameters;

ParameterValue::ParameterValue()
{
}

ParameterValue::~ParameterValue()
{
}

Scheme *ParameterValue::scheme()
{
    return m_scheme;
}

Parameter *ParameterValue::parameter()
{
    return m_parameter;
}

void ParameterValue::setScheme(Scheme *value)
{
    m_scheme = value;
}

void ParameterValue::setParameter(Parameter *value)
{
    m_parameter = value;
}
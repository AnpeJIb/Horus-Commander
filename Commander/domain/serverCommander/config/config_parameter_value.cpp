#include "config_parameter_value.h"

using namespace Domain::ServerCommander::Config;

ConfigParameter* ConfigParameterValue::parameter()
{
    // TODO: NULL-CHECK
    return m_parameter;
}

void ConfigParameterValue::setParameter(ConfigParameter *value)
{
    // TODO: NULL-CHECK
    m_parameter = value;
}

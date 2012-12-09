#include "config_scheme_carrier.h"

using namespace Domain::ServerCommander::Config;

ConfigScheme* ConfigSchemeCarrier::configScheme()
{
    // TODO: NULL-CHECK
    return m_configScheme;
}

void ConfigSchemeCarrier::setConfigScheme(ConfigScheme *value)
{
    // TODO: NULL-CHECK
    m_configScheme = value;
}

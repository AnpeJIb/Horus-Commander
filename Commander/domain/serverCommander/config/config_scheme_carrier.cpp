#include "config_scheme_carrier.h"

Domain::ServerCommander::Config::ConfigScheme*
    Domain::ServerCommander::Config::ConfigSchemeCarrier::configScheme()
{
    // TODO: NULL-CHECK
    return m_configScheme;
}

void Domain::ServerCommander::Config::ConfigSchemeCarrier::setConfigScheme(
        Domain::ServerCommander::Config::ConfigScheme *value)
{
    // TODO: NULL-CHECK
    m_configScheme = value;
}

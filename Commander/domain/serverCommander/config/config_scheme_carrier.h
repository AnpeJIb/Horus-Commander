#ifndef CONFIG_SCHEME_CARRIER_H
#define CONFIG_SCHEME_CARRIER_H

#include "config_scheme.h"

namespace Domain { namespace ServerCommander { namespace Config {

class ConfigSchemeCarrier
{
public:
    ConfigSchemeCarrier();

    ConfigScheme* configScheme();
    void setConfigScheme(ConfigScheme* value);

private:
    ConfigScheme* m_configScheme;
};

}}}

#endif // CONFIG_SCHEME_CARRIER_H

#ifndef CONFIG_PARAMETER_VALUE_H
#define CONFIG_PARAMETER_VALUE_H

#include <QString>

#include "generic_domain.h"
#include "config_scheme_carrier.h"
#include "config_parameter.h"


namespace Domain { namespace ServerCommander { namespace Config {

class ConfigParameterValue: public GenericDomain, public ConfigSchemeCarrier
{
public:
    ConfigParameterValue();

    QString value;

    ConfigParameter* parameter();
    void setParameter(ConfigParameter* value);

private:
    ConfigParameter* m_parameter;
};

}}}

#endif // CONFIG_PARAMETER_VALUE_H

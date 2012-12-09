#ifndef CONFIG_PARAMETER_H
#define CONFIG_PARAMETER_H

#include <QString>
#include "generic_domain.h"
#include "titled_domain.h"

namespace Domain { namespace ServerCommander { namespace Config {

class ConfigParameter: public GenericDomain, public TitledDomain
{
public:
    ConfigParameter();

    QString codeName;
};

}}}

#endif // CONFIG_PARAMETER_H

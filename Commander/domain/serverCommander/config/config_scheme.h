#ifndef CONFIG_SCHEME_H
#define CONFIG_SCHEME_H

#include <QString>
#include "generic_domain.h"

namespace Domain { namespace ServerCommander { namespace Config {

class ConfigScheme: public GenericDomain
{
public:
    ConfigScheme();

    QString title;
    QString description;
    bool trainingModeOnly;
};

}}}

#endif // CONFIG_SCHEME_H

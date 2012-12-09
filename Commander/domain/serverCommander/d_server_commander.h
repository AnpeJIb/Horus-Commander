#ifndef D_SERVER_COMMANDER_H
#define D_SERVER_COMMANDER_H

#include <QString>

#include "generic_domain.h"
#include "titled_domain.h"
#include "config_scheme_carrier.h"
#include "config_parameter.h"

namespace Domain { namespace ServerCommander {

using namespace Config;

class ServerCommanderD: public GenericDomain, public ConfigSchemeCarrier, public TitledDomain
{
public:
    ServerCommanderD();

    QString address;
};

}}

#endif // D_SERVER_COMMANDER_H

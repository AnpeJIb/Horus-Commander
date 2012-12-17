#ifndef COMMANDER_INFO_H
#define COMMANDER_INFO_H

#include <QString>

#include "generic_domain.h"
#include "title_carrier.h"
#include "scheme_carrier.h"

using namespace Domain::Parameters;

namespace Domain {

class CommanderInfo: public GenericDomain, public TitleCarrier, public SchemeCarrier
{
public:
    CommanderInfo();
    ~CommanderInfo();

    Scheme* scheme();
    void setScheme(Scheme* value);

    QString address;
};

}

#endif // COMMANDER_INFO_H

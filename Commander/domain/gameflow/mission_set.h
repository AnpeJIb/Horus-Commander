#ifndef MISSION_SET_H
#define MISSION_SET_H

#include "generic_domain.h"
#include "title_carrier.h"
#include "description_carrier.h"

namespace Domain { namespace Gameflow {

class MissionSet: public GenericDomain, public TitleCarrier, public DescriptionCarrier
{
public:
    MissionSet();
    ~MissionSet();

    bool isEditable;
};

}}

#endif // MISSION_SET_H

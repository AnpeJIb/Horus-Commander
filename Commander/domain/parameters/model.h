#ifndef MODEL_H
#define MODEL_H

#include "generic_domain.h"
#include "title_carrier.h"
#include "kind_carrier.h"

namespace Domain { namespace Parameters {

class Model: public GenericDomain, public TitleCarrier, public KindCarrier
{
public:
    enum MODEL_TYPE
    {
        SETTINGS_PRIMARY = 0,
        SETTINGS_MAIN    = 1,
        MISSION_FINISH   = 2,
        AWARD_ASSIGN     = 3
    };

    Model();
    ~Model();
};

}}

#endif // MODEL_H

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
        MODEL_PRIMARY_SETTINGS = 0,
        MODEL_MAIN_SETTINGS    = 1,
        MODEL_MISSION_FINISH   = 2,
        MODEL_AWARD_ASSIGN     = 3
    };

    Model();
    ~Model();
};

}}

#endif // MODEL_H

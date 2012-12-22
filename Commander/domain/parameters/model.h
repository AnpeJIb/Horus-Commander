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
        MODEL_SETTINGS          = 0,
        MODEL_MISSION_FINISH    = 1,
        MODEL_AWARD_ASSIGN      = 2
    };

    Model();
    ~Model();
};

}}

#endif // MODEL_H

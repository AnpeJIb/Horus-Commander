#ifndef MODEL_H
#define MODEL_H

#include "generic_domain.h"
#include "title_carrier.h"
#include "kind_carrier.h"

namespace Domain { namespace Parameters {

class Model: public GenericDomain, public TitleCarrier, public KindCarrier
{
public:
    Model();
    ~Model();
};

}}

#endif // MODEL_H

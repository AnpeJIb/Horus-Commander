#ifndef MODEL_H
#define MODEL_H

#include "generic_domain.h"
#include "title_carrier.h"
#include "type_carrier.h"

namespace Domain { namespace Parameters {

class Model: public GenericDomain, public TitleCarrier, public TypeCarrier
{
public:
    Model();
    ~Model();
};

}}

#endif // MODEL_H

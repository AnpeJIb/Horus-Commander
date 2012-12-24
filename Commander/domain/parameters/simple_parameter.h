#ifndef SIMPLE_PARAMETER_H
#define SIMPLE_PARAMETER_H

#include "generic_domain.h"
#include "title_carrier.h"
#include "code_name_carrier.h"

namespace Domain { namespace Parameters {

class SimpleParameter: public GenericDomain, public TitleCarrier, public CodeNameCarrier
{
public:
    SimpleParameter(){}
};

}}

#endif // SIMPLE_PARAMETER_H

#ifndef SCHEME_CARRIER_H
#define SCHEME_CARRIER_H

#include "scheme.h"

namespace Domain { namespace Parameters {

class SchemeCarrier
{
public:
    virtual Scheme* scheme() = 0;
    virtual void setScheme(Scheme* value) = 0;

protected:
    Scheme* m_scheme;
};

}}

#endif // SCHEME_CARRIER_H

#ifndef SCHEME_CARRIER_H
#define SCHEME_CARRIER_H

#include <QtCore>
#include "scheme.h"

namespace Domain { namespace Parameters {

class SchemeCarrier
{
public:
    SchemeCarrier() : m_scheme(NULL){}
    virtual Scheme* scheme() = 0;
    virtual void setScheme(Scheme* value) = 0;

protected:
    Scheme* m_scheme;
};

}}

#endif // SCHEME_CARRIER_H

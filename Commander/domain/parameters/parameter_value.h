#ifndef PARAMETER_VALUE_H
#define PARAMETER_VALUE_H

#include <QString>
#include "generic_domain.h"
#include "parameter.h"
#include "scheme_carrier.h"

namespace Domain { namespace Parameters {

class ParameterValue: public GenericDomain, public SchemeCarrier
{
public:
    ParameterValue();
    ~ParameterValue();

    Scheme* scheme();
    Parameter* parameter();

    void setScheme(Scheme* value);
    void setParameter(Parameter* value);

    QString value;

private:
    Parameter* m_parameter;
};

}}

#endif // PARAMETER_VALUE_H

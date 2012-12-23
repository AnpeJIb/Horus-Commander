#ifndef PARAMETER_VALUE_H
#define PARAMETER_VALUE_H

#include <QString>
#include "generic_domain.h"
#include "model_parameter.h"
#include "scheme_carrier.h"

namespace Domain { namespace Parameters {

class ParameterValue: public GenericDomain, public SchemeCarrier
{
public:
    ParameterValue();
    ~ParameterValue();

    Scheme* scheme();
    ModelParameter* parameter();

    void setScheme(Scheme* value);
    void setParameter(ModelParameter* value);

    QString value;

private:
    ModelParameter* m_parameter;
};

}}

#endif // PARAMETER_VALUE_H

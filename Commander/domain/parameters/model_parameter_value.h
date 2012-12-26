#ifndef MODEL_PARAMETER_VALUE_H
#define MODEL_PARAMETER_VALUE_H

#include <QString>
#include "generic_domain.h"
#include "model_parameter.h"
#include "scheme_carrier.h"

namespace Domain { namespace Parameters {

class ModelParameterValue: public GenericDomain, public SchemeCarrier
{
public:
    ModelParameterValue();
    ~ModelParameterValue();

    Scheme* scheme();
    ModelParameter* parameter();

    void setScheme(Scheme* value);
    void setParameter(ModelParameter* value);

    QString value;

private:
    ModelParameter* m_parameter;
};

}}

#endif // MODEL_PARAMETER_VALUE_H

#include "model_parameter_value.h"

#include <QObject>

using namespace Domain;
using namespace Domain::Parameters;

ModelParameterValue::ModelParameterValue(ModelParameterValueHelper *helper)
    : value(QObject::tr("No value")),
      m_parameter(NULL),
      m_helper(helper->clone())
{
}

ModelParameterValue::~ModelParameterValue()
{
    delete m_helper;
}

Scheme *ModelParameterValue::scheme()
{
    if (m_scheme == NULL) m_helper->loadScheme(this);
    return m_scheme;
}

ModelParameter *ModelParameterValue::parameter()
{
    if (m_parameter == NULL) m_helper->loadModelParameter(this);
    return m_parameter;
}

void ModelParameterValue::setScheme(Scheme *value)
{
    m_scheme = value;
}

void ModelParameterValue::setParameter(ModelParameter *value)
{
    m_parameter = value;
}
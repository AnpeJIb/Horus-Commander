#include "parameter.h"

using namespace Domain;
using namespace Domain::Parameters;

Parameter::Parameter()
{
}

Parameter::~Parameter()
{
}

Parameter *Parameter::parent()
{
    return m_parent;
}

Model *Parameter::model()
{
    return m_model;
}

void Parameter::setParent(Parameter *value)
{
    m_parent = value;
}

void Parameter::setModel(Model *value)
{
    m_model = value;
}

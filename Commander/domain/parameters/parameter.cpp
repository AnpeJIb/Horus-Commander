#include "parameter.h"

using namespace Domain;
using namespace Domain::Parameters;

Parameter::Parameter()
    : m_model(NULL)
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

void Parameter::setParent(Parameter *parent)
{
    if (parent != NULL)
        m_model = parent->model();

    m_parent = parent;
}

void Parameter::setModel(Model *model)
{
    m_model = model;
}

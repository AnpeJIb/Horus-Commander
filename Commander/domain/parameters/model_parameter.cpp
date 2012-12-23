#include "model_parameter.h"

using namespace Domain;
using namespace Domain::Parameters;

ModelParameter::ModelParameter()
    : m_model(NULL)
{
}

ModelParameter::~ModelParameter()
{
}

ModelParameter *ModelParameter::parent()
{
    return m_parent;
}

Model *ModelParameter::model()
{
    return m_model;
}

void ModelParameter::setParent(ModelParameter *parent)
{
    if (parent != NULL)
        m_model = parent->model();

    m_parent = parent;
}

void ModelParameter::setModel(Model *model)
{
    m_model = model;
}

#include "model_parameter.h"

using namespace Domain;
using namespace Domain::Parameters;

ModelParameter::ModelParameter(ModelParameterHelper *helper)
    : m_simpleParameter(NULL),
      m_helper(helper->clone())
{
}

ModelParameter::~ModelParameter()
{
    delete m_helper;
}

ModelParameter *ModelParameter::parent()
{
    if (m_parent == NULL) m_helper->loadParent(this);
    return m_parent;
}

Model *ModelParameter::model()
{
    if (m_model == NULL) m_helper->loadModel(this);
    return m_model;
}

SimpleParameter *ModelParameter::simpleParameter()
{
    if (m_simpleParameter == NULL) m_helper->loadSimpleParameter(this);
    return m_simpleParameter;
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

void ModelParameter::setSimpleParameter(SimpleParameter *parameter)
{
    m_simpleParameter = parameter;
}

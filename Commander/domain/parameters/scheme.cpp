#include "scheme.h"

using namespace Domain;
using namespace Domain::Parameters;

Scheme::Scheme(SchemeHelper *helper)
    : m_helper(helper)
{
}

Scheme::~Scheme()
{
}

Model *Scheme::model()
{
    if (m_model == NULL) m_helper->loadModel(this);
    return m_model;
}

void Scheme::setModel(Model *value)
{
    m_model = value;
}

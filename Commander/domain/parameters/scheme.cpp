#include "scheme.h"

using namespace Domain;
using namespace Domain::Parameters;

Scheme::Scheme()
{
}

Scheme::~Scheme()
{
}

Model *Scheme::model()
{
    return m_model;
}

void Scheme::setModel(Model *value)
{
    m_model = value;
}

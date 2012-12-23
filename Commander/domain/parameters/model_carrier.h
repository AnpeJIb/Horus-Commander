#ifndef MODEL_CARRIER_H
#define MODEL_CARRIER_H

#include "model.h"

namespace Domain { namespace Parameters {

class ModelCarrier
{
public:
    ModelCarrier():m_model(NULL){}

    virtual Model* model() = 0;
    virtual void setModel(Model* model) = 0;

protected:
    Model* m_model;
};

}}

#endif // MODEL_CARRIER_H

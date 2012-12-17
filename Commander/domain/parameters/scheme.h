#ifndef SCHEME_H
#define SCHEME_H

#include "generic_domain.h"
#include "title_carrier.h"
#include "description_carrier.h"
#include "model.h"

namespace Domain { namespace Parameters {

class Scheme: public GenericDomain, public TitleCarrier, public DescriptionCarrier
{
public:
    Scheme();
    ~Scheme();

    Model* model();
    void setModel(Model* value);

private:
    Model* m_model;
};

}}

#endif // SCHEME_H

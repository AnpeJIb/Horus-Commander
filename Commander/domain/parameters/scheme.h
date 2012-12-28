#ifndef SCHEME_H
#define SCHEME_H

#include "generic_domain.h"
#include "title_carrier.h"
#include "description_carrier.h"
#include "model_carrier.h"
#include "scheme_helper.h"

namespace Domain { namespace Parameters {

class Scheme: public GenericDomain, public TitleCarrier, public DescriptionCarrier, public ModelCarrier
{
public:
    explicit Scheme(SchemeHelper *helper);
    ~Scheme();

    Model* model();
    void setModel(Model* value);

private:
    SchemeHelper* m_helper;
};

}}

#endif // SCHEME_H

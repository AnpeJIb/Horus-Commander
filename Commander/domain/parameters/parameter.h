#ifndef PARAMETER_H
#define PARAMETER_H

#include "generic_domain.h"
#include "title_carrier.h"
#include "code_name_carrier.h"
#include "kind_carrier.h"
#include "parent_carrier.h"
#include "model.h"
#include "logical_operation_types.h"

namespace Domain { namespace Parameters {

class Parameter;

class Parameter:
        public GenericDomain,
        public TitleCarrier,
        public CodeNameCarrier,
        public KindCarrier,
        public ParentCarrier<Parameter>
{
public:
    Parameter();
    ~Parameter();

    Parameter* parent();
    Model* model();

    void setParent(Parameter* parent);
    void setModel(Model* model);

private:
    Model* m_model;
};

}}

#endif // PARAMETER_H

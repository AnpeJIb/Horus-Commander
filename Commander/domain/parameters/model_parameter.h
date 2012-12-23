#ifndef PARAMETER_H
#define PARAMETER_H

#include "generic_domain.h"
#include "title_carrier.h"
#include "kind_carrier.h"
#include "parent_carrier.h"
#include "model_carrier.h"
#include "simple_parameter.h"
#include "logical_operation_types.h"

namespace Domain { namespace Parameters {

class ModelParameter;

class ModelParameter:
        public GenericDomain,
        public TitleCarrier,
        public KindCarrier,
        public ModelCarrier,
        public ParentCarrier<ModelParameter>
{
public:
    ModelParameter();
    ~ModelParameter();

    ModelParameter* parent();
    Model* model();
    SimpleParameter* simpleParameter();

    void setParent(ModelParameter* parent);
    void setModel(Model* model);
    void setSimpleParameter(SimpleParameter* parameter);

private:
    SimpleParameter* m_simpleParameter;
};

}}

#endif // PARAMETER_H

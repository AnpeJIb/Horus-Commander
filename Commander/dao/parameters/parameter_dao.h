#ifndef PARAMETER_DAO_H
#define PARAMETER_DAO_H

#include "generic_dao.h"
#include "title_carrier_dao.h"
#include "kind_carrier_dao.h"
#include "code_name_carrier_dao.h"
#include "parameter.h"

using namespace Domain::Parameters;

namespace Dao { namespace Parameters {

class ParameterDao:
        public GenericDao<Parameter>,
        public TitleCarrierDao<Parameter>,
        public KindCarrierDao<Parameter>,
        public CodeNameCarrierDao<Parameter>
{
public:
};

}}

#endif // PARAMETER_DAO_H

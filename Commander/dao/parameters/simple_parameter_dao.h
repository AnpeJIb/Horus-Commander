#ifndef SIMPLE_PARAMETER_DAO_H
#define SIMPLE_PARAMETER_DAO_H

#include "generic_dao.h"
#include "title_carrier_dao.h"
#include "code_name_carrier_dao.h"
#include "simple_parameter.h"

using namespace Domain::Parameters;

namespace Dao { namespace Parameters {

class SimpleParameterDao:
        public GenericDao<SimpleParameter>,
        public TitleCarrierDao<SimpleParameter>,
        public CodeNameCarrierDao<SimpleParameter>
{
};

}}

#endif // SIMPLE_PARAMETER_DAO_H

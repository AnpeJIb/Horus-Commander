#ifndef SCHEME_DAO_H
#define SCHEME_DAO_H

#include "generic_dao.h"
#include "scheme.h"
#include "scheme_helper.h"

#include "title_carrier_dao.h"
#include "description_carrier_dao.h"
#include "model_carrier_dao.h"

using namespace Domain::Parameters;

namespace Dao { namespace Parameters {

class SchemeDao:
        public GenericDao<Scheme>,
        public TitleCarrierDao<Scheme>,
        public DescriptionCarrierDao<Scheme>,
        public ModelCarrierDao<Scheme>,
        public SchemeHelper
{
};

}}

#endif // SCHEME_DAO_H

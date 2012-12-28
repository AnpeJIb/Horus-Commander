#ifndef SCHEME_HELPER_H
#define SCHEME_HELPER_H

#include "scheme.h"
#include "domain_helper.h"

namespace Domain { namespace Parameters {

class Scheme;
class SchemeHelper;

class SchemeHelper: public DomainHelper<SchemeHelper>
{
public:
    virtual void loadModel(Scheme* domain) = 0;
};

}}


#endif // SCHEME_HELPER_H

#ifndef SCHEME_JUDGE_H
#define SCHEME_JUDGE_H

#include "title_judge.h"
#include "scheme.h"

namespace Domain { namespace Parameters {

class SchemeJudge: public TitleJudge<Domain::Parameters::Scheme>
{
public:
    virtual ~SchemeJudge(){}
};

}}

#endif // SCHEME_JUDGE_H

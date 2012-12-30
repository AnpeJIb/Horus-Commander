#ifndef TITLE_JUDGE_H
#define TITLE_JUDGE_H

#include "title_carrier.h"

namespace Domain {

template <class T> class TitleJudge
{
public:
    virtual bool isTitleAcceptable(const T* carrier, const domain_title_t& title) = 0;

    virtual ~TitleJudge(){}
};

}

#endif // TITLE_JUDGE_H

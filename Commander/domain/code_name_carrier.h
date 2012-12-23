#ifndef CODE_NAME_CARRIER_H
#define CODE_NAME_CARRIER_H

#include <QString>

typedef QString domain_codeName_t;

namespace Domain {

class CodeNameCarrier
{
public:
    virtual ~CodeNameCarrier() = 0;

    domain_codeName_t codeName;
};

inline CodeNameCarrier::~CodeNameCarrier(){}

}

#endif // CODE_NAME_CARRIER_H

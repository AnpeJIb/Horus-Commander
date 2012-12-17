#ifndef CODE_NAME_CARRIER_H
#define CODE_NAME_CARRIER_H

#include <QString>

namespace Domain {

class CodeNameCarrier
{
public:
    virtual ~CodeNameCarrier() = 0;

    QString codeName;
};

inline CodeNameCarrier::~CodeNameCarrier(){}

}

#endif // CODE_NAME_CARRIER_H

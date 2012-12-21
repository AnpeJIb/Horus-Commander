#ifndef TITLE_CARRIER_H
#define TITLE_CARRIER_H

#include <QString>

typedef QString domain_title_t;

namespace Domain {

class TitleCarrier
{
public:
    virtual ~TitleCarrier() = 0;

    domain_title_t title;
};

inline TitleCarrier::~TitleCarrier(){}

}

#endif // TITLE_CARRIER_H

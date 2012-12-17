#ifndef TITLE_CARRIER_H
#define TITLE_CARRIER_H

#include <QString>

namespace Domain {

class TitleCarrier
{
public:
    virtual ~TitleCarrier() = 0;

    QString title;
};

inline TitleCarrier::~TitleCarrier(){}

}

#endif // TITLE_CARRIER_H

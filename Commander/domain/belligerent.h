#ifndef BELLIGERENT_H
#define BELLIGERENT_H

#include <QObject>
#include <QString>

#include "generic_domain.h"
#include "title_carrier.h"

namespace Domain {

class Belligerent: public GenericDomain, public TitleCarrier
{
public:

    enum ARMY_CODE
    {
        ARMY_NONE   = 0,
        ARMY_RED    = 1,
        ARMY_BLUE   = 2
    };

    Belligerent();
    ~Belligerent();

    quint8  armyCode;
    bool    isSelectable;
    QString colorHexCode;
};

}

#endif // BELLIGERENT_H

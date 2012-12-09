#ifndef BELLIGERENT_H
#define BELLIGERENT_H

#include <QObject>
#include <QString>

#include "generic_domain.h"
#include "titled_domain.h"

namespace Domain
{

class Belligerent: public GenericDomain, public TitledDomain
{
public:

    enum ARMY_CODE
    {
        ARMY_NONE   = 0,
        ARMY_RED    = 1,
        ARMY_BLUE   = 2
    };

    Belligerent();

    quint8  armyCode;
    bool    selectable;
    QString colorHexCode;
};

}

#endif // BELLIGERENT_H

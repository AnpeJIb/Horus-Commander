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

    quint8  armyCode() {return m_armyCode;}
    bool    selectable() {return m_selectable;}
    QString colorHexCode() const {return m_colorHexCode;}

    void setArmyCode(quint8 value) {m_armyCode = value;}
    void setSelectable(bool value) {m_selectable = value;}
    void setColorHexCode(const QString& value) {m_colorHexCode = value;}

private:
    quint8  m_armyCode;
    bool    m_selectable;
    QString m_colorHexCode;
};

}

#endif // BELLIGERENT_H

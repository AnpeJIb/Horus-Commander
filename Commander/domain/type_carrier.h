#ifndef TYPE_CARRIER_H
#define TYPE_CARRIER_H

#include <QtCore>

namespace Domain
{

class TypeCarrier
{
public:
    TypeCarrier();
    TypeCarrier(quint8 type);

    quint8 type(){return m_type;}
    void setType(quint8 value){m_type = value;}

protected:
    quint8 m_type;
};

}

#endif // TYPE_CARRIER_H

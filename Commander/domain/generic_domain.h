#ifndef GENERIC_DOMAIN_H
#define GENERIC_DOMAIN_H

#include <QtCore>

namespace Domain
{

class GenericDomain
{
public:
    GenericDomain();
    GenericDomain(quint64 id);

    qlonglong id(){return m_id;}
    void setId(qlonglong value){m_id = value;}

protected:
    qlonglong m_id;
};

}

#endif // GENERIC_DOMAIN_H

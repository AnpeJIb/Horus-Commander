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

    quint64 id(){return m_id;}
    void    setId(quint64 value){m_id = value;}

protected:
    quint64 m_id;
};

}

#endif // GENERIC_DOMAIN_H

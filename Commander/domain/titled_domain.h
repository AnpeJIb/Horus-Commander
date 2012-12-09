#ifndef TITLED_DOMAIN_H
#define TITLED_DOMAIN_H

#include <QString>

namespace Domain
{

class TitledDomain
{
public:
    TitledDomain();
    TitledDomain(const QString& title);

    QString title() const {return m_title;}
    void    setTitle(const QString& value){m_title = value;}

protected:
    QString m_title;
};

}

#endif // TITLED_DOMAIN_H

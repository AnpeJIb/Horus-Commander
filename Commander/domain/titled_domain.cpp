#include "titled_domain.h"
#include <QObject>

Domain::TitledDomain::TitledDomain()
    : m_title(QObject::tr("No title"))
{
}

Domain::TitledDomain::TitledDomain(const QString &title)
    : m_title(title)
{
}

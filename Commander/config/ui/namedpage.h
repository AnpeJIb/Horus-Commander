#ifndef NAMEDPAGE_H
#define NAMEDPAGE_H

#include <QString>

class NamedPage
{
public:
    NamedPage();

    virtual QString pageName() = 0;
};

#endif // NAMEDPAGE_H

#ifndef STRING_COMPOSER_H
#define STRING_COMPOSER_H

#include <QString>

template<typename T> class StringComposer
{
public:
    virtual ~StringComposer(){}

    virtual void compose(const T& source, QString& destination) = 0;
    virtual void decompose(const QString& source, T& destination) = 0;
};

#endif // STRING_COMPOSER_H

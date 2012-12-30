#ifndef SQLITE_CONNECTION_STRING_COMPOSER_H
#define SQLITE_CONNECTION_STRING_COMPOSER_H

#include "string_composer.h"
#include "general_config.h"

namespace Config { namespace General {

class SQLiteConnectionStringComposer: public StringComposer<SQLiteConfig>
{
public:
    SQLiteConnectionStringComposer();

    void compose(const SQLiteConfig &source, QString &destination);
    void decompose(const QString &source, SQLiteConfig &destination);
};

}}

#endif // SQLITE_CONNECTION_STRING_COMPOSER_H

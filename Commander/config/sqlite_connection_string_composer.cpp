#include "sqlite_connection_string_composer.h"

namespace Config { namespace General {

SQLiteConnectionStringComposer::SQLiteConnectionStringComposer()
{
}

void SQLiteConnectionStringComposer::compose(const SQLiteConfig &source, QString &destination)
{
    destination = source.path;
}

void SQLiteConnectionStringComposer::decompose(const QString &source, SQLiteConfig &destination)
{
    destination.path = source;
}

}}

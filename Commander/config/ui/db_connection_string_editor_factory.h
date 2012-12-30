#ifndef DB_CONNECTION_STRING_EDITOR_FACTORY_H
#define DB_CONNECTION_STRING_EDITOR_FACTORY_H

#include "general_config.h"
#include "db_connection_string_editor.h"
#include "sqlite_connection_string_editor.h"

class DBConnectionStringEditorFactory
{
public:
    static DBConnectionStringEditor* getNewEditor(
            Config::General::DB_KIND dbKind, const QString& source, QWidget *parent = 0);
};

DBConnectionStringEditor* DBConnectionStringEditorFactory::getNewEditor(
        Config::General::DB_KIND dbKind, const QString &source, QWidget *parent)
{
    switch (dbKind) {
    case Config::General::DB_SQLITE:
        return new SQLiteConnectionStringEditor(source, parent);
    default:
        return NULL;
    }
}

#endif // DB_CONNECTION_STRING_EDITOR_FACTORY_H

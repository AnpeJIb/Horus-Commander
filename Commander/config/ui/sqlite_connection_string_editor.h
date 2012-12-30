#ifndef SQLITE_CONNECTION_STRING_EDITOR_H
#define SQLITE_CONNECTION_STRING_EDITOR_H

#include <QAbstractButton>

#include "db_connection_string_editor.h"
#include "sqlite_connection_string_composer.h"

namespace Ui {
class SQLiteConnectionStringEditor;
}

class SQLiteConnectionStringEditor : public DBConnectionStringEditor
{
    Q_OBJECT
    
public:
    explicit SQLiteConnectionStringEditor(const QString& source, QWidget *parent = 0);
    ~SQLiteConnectionStringEditor();

    QString editedString();
    
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_dbPathSearch_clicked();

private:
    void load();
    bool isValid();

    Ui::SQLiteConnectionStringEditor *ui;
    Config::General::SQLiteConnectionStringComposer m_composer;
};

#endif // SQLITE_CONNECTION_STRING_EDITOR_H

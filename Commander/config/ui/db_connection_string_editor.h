#ifndef DB_CONNECTION_STRING_EDITOR_H
#define DB_CONNECTION_STRING_EDITOR_H

#include <QDialog>
#include <QString>

class DBConnectionStringEditor: public QDialog
{
    Q_OBJECT
public:
    explicit DBConnectionStringEditor(const QString& source, QWidget *parent = 0) : QDialog(parent), m_source(source){}
    virtual ~DBConnectionStringEditor(){}

    virtual QString editedString() = 0;

protected:
    QString m_source;
};

#endif // DB_CONNECTION_STRING_EDITOR_H

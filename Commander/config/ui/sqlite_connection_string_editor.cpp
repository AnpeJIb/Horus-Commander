#include "sqlite_connection_string_editor.h"
#include "ui_sqlite_connection_string_editor.h"

#include <QObject>
#include <QMessageBox>
#include <QFileDialog>

SQLiteConnectionStringEditor::SQLiteConnectionStringEditor(const QString &source, QWidget *parent) :
    DBConnectionStringEditor(source, parent),
    ui(new Ui::SQLiteConnectionStringEditor)
{
    ui->setupUi(this);
    load();
}

SQLiteConnectionStringEditor::~SQLiteConnectionStringEditor()
{
    delete ui;
}

QString SQLiteConnectionStringEditor::editedString()
{
    QString result;
    Config::General::SQLiteConfig config;

    config.path = ui->dbPath->text();
    m_composer.compose(config, result);

    return result;
}

void SQLiteConnectionStringEditor::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->buttonRole(button))
    {
        case QDialogButtonBox::RejectRole:
            close();
            break;
        case QDialogButtonBox::AcceptRole:
            if (isValid())
                accept();
            break;
        default:;
    }
}

void SQLiteConnectionStringEditor::on_dbPathSearch_clicked()
{
    QString currentPath = ui->dbPath->text();
    QString startDir = (currentPath.isEmpty())?QDir::currentPath():currentPath;

    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Select path to database"),
                startDir);

    if (path.isNull() | path.isEmpty()) return;

    ui->dbPath->setText(path);
}

void SQLiteConnectionStringEditor::load()
{
    Config::General::SQLiteConfig config;
    m_composer.decompose(m_source, config);

    ui->dbPath->setText(config.path);
}

bool SQLiteConnectionStringEditor::isValid()
{
    if (ui->dbPath->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Undefined value"),
                              tr("Path to database is undefined!"),
                              QMessageBox::Close);
        return false;
    }

    return true;
}

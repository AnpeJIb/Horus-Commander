#include "general_config_page.h"
#include "ui_general_config_page.h"

#include <QFileDialog>
#include <QDir>
#include <QList>
#include <QMessageBox>

#include "db_connection_string_editor.h"
#include "db_connection_string_editor_factory.h"

GeneralConfigPage::GeneralConfigPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralConfigPage)
{
    ui->setupUi(this);
    populateBoxes();
}

GeneralConfigPage::~GeneralConfigPage()
{
    delete ui;
}

void GeneralConfigPage::populateBoxes()
{
    populateLangs();
    populateDBs();
}

void GeneralConfigPage::populateLangs()
{
    QList<Config::General::SupportedLanguage> lst = Config::General::supportedLanguages();

    foreach (Config::General::SupportedLanguage lang, lst)
    {
        ui->langBox->addItem(lang.icon, lang.title, lang.codeName);
    }
}

void GeneralConfigPage::populateDBs()
{
    QList<Config::General::SupportedDB> lst = Config::General::supportedDatabases();

    foreach (Config::General::SupportedDB db, lst)
    {
        ui->dbBox->addItem(db.title, db.kind);
    }
}

bool GeneralConfigPage::isValid()
{
    if (ui->serverPath->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Undefined value"),
                              tr("Path to server is undefined!"),
                              QMessageBox::Close);
        return false;
    }

    return true;
}

void GeneralConfigPage::save()
{
    m_service.setLanguageCode(ui->langBox->itemData(ui->langBox->currentIndex()).toString());
    m_service.setServerPath(ui->serverPath->text());
    m_service.setDbKind(selectedDBkind());
}

void GeneralConfigPage::load()
{
    ui->serverPath->setText(m_service.serverPath());
    selectLangInBox(m_service.languageCode());
    selectDBInBox(m_service.dbKind());
}

void GeneralConfigPage::loadDefaults()
{
    ui->serverPath->setText(Config::General::defaultServerPath());
    selectLangInBox(Config::General::defaultLanguage().codeName);
    selectDBInBox((Config::General::DB_KIND) Config::General::defaultDB().kind);
}

void GeneralConfigPage::setConfigEnabled(bool value)
{
    ui->langBox->setEnabled(value);
    ui->serverPath->setEnabled(value);
    ui->serverPathSearch->setEnabled(value);

    bool dbValue = value && (ui->dbBox->count() > 0);
    ui->dbBox->setEnabled(dbValue);
    ui->dbEdit->setEnabled(dbValue);
    ui->dbConnectionState->setEnabled(dbValue);
}

void GeneralConfigPage::selectLangInBox(QString lang)
{
    int id = ui->langBox->findData(lang);
    ui->langBox->setCurrentIndex((id<0)?0:id);
}

void GeneralConfigPage::selectDBInBox(Config::General::DB_KIND dbKind)
{
    int id = ui->dbBox->findData(dbKind);
    ui->dbBox->setCurrentIndex((id<0)?0:id);
}

Config::General::DB_KIND GeneralConfigPage::selectedDBkind()
{
    return (Config::General::DB_KIND) ui->dbBox->itemData(ui->dbBox->currentIndex()).toUInt();
}

QString GeneralConfigPage::pageName()
{
    return ui->pageName->text();
}

void GeneralConfigPage::on_serverPathSearch_clicked()
{
    QString currentPath = ui->serverPath->text();
    QString startDir = (currentPath.isEmpty())?QDir::currentPath():currentPath;

    QString path = QFileDialog::getExistingDirectory(
                this,
                tr("Select server directory"),
                startDir,
                QFileDialog::ShowDirsOnly);

    if (path.isNull() | path.isEmpty()) return;

    ui->serverPath->setText(path);
}

void GeneralConfigPage::on_dbEdit_clicked()
{
    Config::General::DB_KIND dbKind = selectedDBkind();

    DBConnectionStringEditor* editor =
            DBConnectionStringEditorFactory::getNewEditor(dbKind, m_service.dbConnectionString(dbKind));

    if (editor->exec() == QDialog::Accepted)
        m_service.setDbConnectionString(dbKind, editor->editedString());

    delete editor;
}

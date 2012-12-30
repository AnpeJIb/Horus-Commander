#include "general_config_page.h"
#include "ui_general_page.h"

#include <QFileDialog>
#include <QDir>
#include <QList>
#include <QMessageBox>

GeneralConfigPage::GeneralConfigPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralPage)
{
    ui->setupUi(this);
    populateLangs();
}

GeneralConfigPage::~GeneralConfigPage()
{
    delete ui;
}

bool GeneralConfigPage::isValid()
{
    return true;
}

void GeneralConfigPage::save()
{
    service.setLanguageCode(ui->langBox->itemData(ui->langBox->currentIndex()).toString());
    service.setServerPath(ui->serverPath->text());

    //    if (ui->serverPath->text().isEmpty())
    //    {
    //        QMessageBox::critical(this,
    //                              tr("Server's path"),
    //                              tr("Server's path is not set!"),
    //                              QMessageBox::Close);
    //        return false;
    //    }

    //    if (ui->serverName->text().isEmpty())
    //    {
    //        QMessageBox::critical(this,
    //                              tr("Server's name"),
    //                              tr("Server's name is not set!"),
    //                              QMessageBox::Close);
    //        return false;
    //    }

    //    QString langCode = ui->langBox->itemData(ui->langBox->currentIndex()).toString();

    //    if (langCode!=CONFIG::GENERAL.langCode())
    //    {
    //        QMessageBox::information(this,
    //                              tr("Language changed"),
    //                              tr("Restart application to apply new language."),
    //                              QMessageBox::Ok);
    //    }
}

void GeneralConfigPage::load()
{
    ui->serverPath->setText(service.serverPath());
    selectLangInBox(service.languageCode());
}

void GeneralConfigPage::loadDefaults()
{
    ui->serverPath->setText(Config::General::defaultServerPath());
    selectLangInBox(Config::General::defaultLanguageCode());
}

void GeneralConfigPage::setConfigEnabled(bool value)
{
    ui->langBox->setEnabled(value);
    ui->serverPath->setEnabled(value);
    ui->serverPathSearch->setEnabled(value);
    // TODO: DB
}

void GeneralConfigPage::populateLangs()
{
    QList<Config::General::AvailableLanguage> lst = Config::General::availableLanguages();

    foreach (Config::General::AvailableLanguage lang, lst)
    {
        ui->langBox->addItem(lang.icon, lang.title, lang.codeName);
    }
}

void GeneralConfigPage::selectLangInBox(QString lang)
{
    int id = ui->langBox->findData(lang);
    ui->langBox->setCurrentIndex((id<0)?0:id);
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

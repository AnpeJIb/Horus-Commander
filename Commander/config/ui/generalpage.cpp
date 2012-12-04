#include "generalpage.h"
#include "ui_generalpage.h"
#include "config.h"

#include <QFileDialog>
#include <QMessageBox>

GeneralPage::GeneralPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralPage)
{
    ui->setupUi(this);
    populateLangs();
}

GeneralPage::~GeneralPage()
{
    delete ui;
}

bool GeneralPage::save()
{
    if (ui->serverPath->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Server's path"),
                              tr("Server's path is not set!"),
                              QMessageBox::Close);
        return false;
    }

    if (ui->serverName->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Server's name"),
                              tr("Server's name is not set!"),
                              QMessageBox::Close);
        return false;
    }

    if ((ui->isDaemon->isChecked()!=CONFIG::GENERAL.isDaemonMode())
    &&   ui->isDaemon->isChecked())
    {
        QMessageBox::information(this,
                              tr("Daemon mode"),
                              tr("Commander will run in daemon mode next time!\n"
                                 "You will be able to change it in config file."),
                              QMessageBox::Ok);
    }

    QString langCode = ui->langBox->itemData(ui->langBox->currentIndex()).toString();

    if (langCode!=CONFIG::GENERAL.langCode())
    {
        QMessageBox::information(this,
                              tr("Language changed"),
                              tr("Restart application to apply new language."),
                              QMessageBox::Ok);
    }

    CONFIG::GENERAL.setLangCode(    langCode);
    CONFIG::GENERAL.setDaemonMode(  ui->isDaemon->isChecked());
    CONFIG::GENERAL.setServerPath(  ui->serverPath->text());
    CONFIG::GENERAL.setServerName(  ui->serverName->text());
    CONFIG::GENERAL.setServerDescr( ui->serverDescr->text());

    return true;
}

void GeneralPage::load()
{
    ui->serverPath->setText(    CONFIG::GENERAL.serverPath());
    ui->serverName->setText(    CONFIG::GENERAL.serverName());
    ui->serverDescr->setText(   CONFIG::GENERAL.serverDescr());
    ui->isDaemon->setChecked(   CONFIG::GENERAL.isDaemonMode());
    selectLangInBox(            CONFIG::GENERAL.langCode());
}

void GeneralPage::loadDefaults()
{
    ui->serverPath->setText(    DEFAULT_SERVER_PATH);
    ui->serverName->setText(    DEFAULT_SERVER_NAME);
    ui->serverDescr->setText(   DEFAULT_SERVER_DESCR);
    ui->isDaemon->setChecked(   DEFAULT_DEAMON_MODE);
    selectLangInBox(            DEFAULT_LANG_CODE);
}

void GeneralPage::on_serverPathBrowse_clicked()
{
    QString currentPath = ui->serverPath->text();
    QString startDir = (currentPath.isEmpty())?"./":currentPath;

    QString path = QFileDialog::getExistingDirectory(
                this,
                tr("Select server directory"),
                startDir,
                QFileDialog::ShowDirsOnly);

    if (path.isNull() | path.isEmpty()) return;

    ui->serverPath->setText(path);
}

void GeneralPage::populateLangs()
{
    ui->langBox->addItem(QIcon(":/img/langEn.png"), tr("English"), LANG_CODE_EN);
    ui->langBox->addItem(QIcon(":/img/langRu.png"), tr("Russian"), LANG_CODE_RU);
}

void GeneralPage::selectLangInBox(QString lang)
{
    int id = ui->langBox->findData(lang);
    ui->langBox->setCurrentIndex((id<0)?0:id);
}

QString GeneralPage::pageName()
{
    return ui->pageName->text();
}

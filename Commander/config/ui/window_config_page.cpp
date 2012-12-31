#include "window_config_page.h"
#include "ui_window_config_page.h"

#include "window_config.h"

WindowConfigPage::WindowConfigPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowConfigPage)
{
    ui->setupUi(this);
}

WindowConfigPage::~WindowConfigPage()
{
    delete ui;
}

bool WindowConfigPage::isValid()
{
    return true;
}

void WindowConfigPage::save()
{
    m_service.setStartMinimized(     ui->startMinimized->isChecked());
    m_service.setQuitOnClose(        ui->quitOnClose->isChecked());
    m_service.setAskQuitConfirmation(ui->askQuitConfirmation->isChecked());
    m_service.setRunAsDaemon(        ui->runAsDaemon->isChecked());
}

void WindowConfigPage::load()
{
    ui->startMinimized->setChecked(     m_service.startMinimized());
    ui->quitOnClose->setChecked(        m_service.quitOnClose());
    ui->askQuitConfirmation->setChecked(m_service.askQuitConfirmation());
    ui->runAsDaemon->setChecked(        m_service.runAsDaemon());
}

void WindowConfigPage::loadDefaults()
{
    ui->startMinimized->setChecked(     Config::Window::defaultStartMinimized);
    ui->quitOnClose->setChecked(        Config::Window::defaultQuitOnlose);
    ui->askQuitConfirmation->setChecked(Config::Window::defaultAskQuitConfirmation);
    ui->runAsDaemon->setChecked(        Config::Window::defaultRunAsDaemon);
}

void WindowConfigPage::setConfigEnabled(bool value)
{
    ui->startMinimized->setEnabled(value);
    ui->quitOnClose->setEnabled(value);
    ui->askQuitConfirmation->setEnabled(value);
    ui->runAsDaemon->setEnabled(value);
}

QString WindowConfigPage::pageName() const
{
    return ui->pageName->text();
}

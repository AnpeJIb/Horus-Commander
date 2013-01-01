#include "log_config_page.h"
#include "ui_log_config_page.h"

#include <QVBoxLayout>
#include "common_log_config_page.h"
#include "log_config.h"

LogConfigPage::LogConfigPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogConfigPage)
{
    ui->setupUi(this);
    addListedStack();
    addPages();
}

LogConfigPage::~LogConfigPage()
{
    delete ui;
}

bool LogConfigPage::isValid()
{
    return areChildrenValid();
}

void LogConfigPage::save()
{
    saveChildren();
}

void LogConfigPage::load()
{
    loadChildren();
}

void LogConfigPage::loadDefaults()
{
    loadChildrenDefaults();
}

void LogConfigPage::setConfigEnabled(bool value)
{
    setConfigChildrenEnabled(value);
}

QString LogConfigPage::pageName() const
{
    return ui->pageName->text();
}

void LogConfigPage::addListedStack()
{
    listedStack = new ListedStack(30, 150, this);
    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(listedStack);
    ui->stackedListHolder->setLayout(l);
}

void LogConfigPage::addPages()
{
    CommonLogConfigPage* fileLog = new CommonLogConfigPage(tr("File"), Config::Log::LOG_FILE);
    listedStack->addPage(fileLog->pageName(), fileLog);
    addChild(fileLog);

    CommonLogConfigPage* guiLog = new CommonLogConfigPage(tr("GUI"), Config::Log::LOG_GUI);
    listedStack->addPage(guiLog->pageName(), guiLog);
    addChild(guiLog);

    listedStack->setCurrentIndex(0);
}

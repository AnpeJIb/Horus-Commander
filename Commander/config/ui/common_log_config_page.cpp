#include "common_log_config_page.h"
#include "ui_common_log_config_page.h"
#include "bitwise.h"

CommonLogConfigPage::CommonLogConfigPage(const QString& name, Config::Log::LOG_KIND kind, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonLogConfigPage),
    m_kind(kind)
{
    ui->setupUi(this);
    ui->pageName->setText(name);
}

CommonLogConfigPage::~CommonLogConfigPage()
{
    delete ui;
}

bool CommonLogConfigPage::isValid()
{
    return true;
}

void CommonLogConfigPage::save()
{
    m_service.setLogLevel(m_kind, (StatusPrinter::Level) m_currentLevel);
}

void CommonLogConfigPage::load()
{
    loadLevel(m_service.logLevel(m_kind));
}

void CommonLogConfigPage::loadDefaults()
{
    loadLevel(Config::Log::defaultLogLevel);
}

void CommonLogConfigPage::setConfigEnabled(bool value)
{
    bool endValue = value;
    ui->ch_disabled->setEnabled(endValue);

    endValue &= (ui->ch_disabled->isChecked() == false);
    ui->ch_all->setEnabled(endValue);

    endValue &= (ui->ch_all->isChecked() == false);
    setGroupEnabled(endValue);
}

QString CommonLogConfigPage::pageName() const
{
    return ui->pageName->text();
}

void CommonLogConfigPage::on_ch_disabled_clicked()
{
    m_currentLevel = StatusPrinter::LEVEL_NONE;

    bool value = ui->ch_disabled->isChecked();

    if (value)
    {
        ui->ch_all->setChecked(false);
        setGroupChecked(false);
    }

    value = !value;

    ui->ch_all->setEnabled(value);
    setGroupEnabled(value);
}

void CommonLogConfigPage::on_ch_all_clicked()
{
    m_currentLevel = StatusPrinter::LEVEL_ALL;

    bool value = ui->ch_all->isChecked();

    if (value)
        setGroupChecked(true);

    setGroupEnabled(!value);
}

void CommonLogConfigPage::loadLevel(StatusPrinter::Level level)
{
    if (level == StatusPrinter::LEVEL_NONE)
    {
        ui->ch_disabled->setChecked(true);
        on_ch_disabled_clicked();
        return;
    }

    if (level == StatusPrinter::LEVEL_ALL)
    {
        ui->ch_all->setChecked(true);
        on_ch_all_clicked();
        return;
    }

    m_currentLevel = level;

    ui->ch_tasks->setChecked(BIT_CHECK_RAW(level, StatusPrinter::LEVEL_TASKS));
    ui->ch_info->setChecked( BIT_CHECK_RAW(level, StatusPrinter::LEVEL_INFO));
    ui->ch_warn->setChecked( BIT_CHECK_RAW(level, StatusPrinter::LEVEL_WARNING));
    ui->ch_err->setChecked(  BIT_CHECK_RAW(level, StatusPrinter::LEVEL_ERROR));
    ui->ch_dbg->setChecked(  BIT_CHECK_RAW(level, StatusPrinter::LEVEL_DEBUG));
}

void CommonLogConfigPage::checkLevel()
{
    if (m_currentLevel == StatusPrinter::LEVEL_NONE)
    {
        ui->ch_disabled->setChecked(true);
        on_ch_disabled_clicked();
        return;
    }

    if (m_currentLevel == StatusPrinter::LEVEL_ALL)
    {
        ui->ch_all->setChecked(true);
        on_ch_all_clicked();
    }
}

void CommonLogConfigPage::setGroupEnabled(bool value)
{
    ui->ch_tasks->setEnabled(value);
    ui->ch_info->setEnabled(value);
    ui->ch_warn->setEnabled(value);
    ui->ch_err->setEnabled(value);
    ui->ch_dbg->setEnabled(value);
}

void CommonLogConfigPage::setGroupChecked(bool value)
{
    ui->ch_tasks->setChecked(value);
    ui->ch_info->setChecked(value);
    ui->ch_warn->setChecked(value);
    ui->ch_err->setChecked(value);
    ui->ch_dbg->setChecked(value);
}

void CommonLogConfigPage::on_ch_tasks_clicked()
{
    BIT_SET_RAW(m_currentLevel, StatusPrinter::LEVEL_TASKS, ui->ch_tasks->isChecked());
    checkLevel();
}

void CommonLogConfigPage::on_ch_info_clicked()
{
    BIT_SET_RAW(m_currentLevel, StatusPrinter::LEVEL_INFO, ui->ch_info->isChecked());
    checkLevel();
}

void CommonLogConfigPage::on_ch_warn_clicked()
{
    BIT_SET_RAW(m_currentLevel, StatusPrinter::LEVEL_WARNING, ui->ch_warn->isChecked());
    checkLevel();
}

void CommonLogConfigPage::on_ch_err_clicked()
{
    BIT_SET_RAW(m_currentLevel, StatusPrinter::LEVEL_ERROR, ui->ch_err->isChecked());
    checkLevel();
}

void CommonLogConfigPage::on_ch_dbg_clicked()
{
    BIT_SET_RAW(m_currentLevel, StatusPrinter::LEVEL_DEBUG, ui->ch_dbg->isChecked());
    checkLevel();
}

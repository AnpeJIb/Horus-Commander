#ifndef COMMON_LOG_CONFIG_PAGE_H
#define COMMON_LOG_CONFIG_PAGE_H

#include <QWidget>

#include "uiconfig_module.h"
#include "named_page.h"
#include "logger.h"
#include "log_config.h"
#include "log_config_service.h"

namespace Ui {
class CommonLogConfigPage;
}

class CommonLogConfigPage : public QWidget, public UIConfigModule, public NamedPage
{
    Q_OBJECT
    
public:
    explicit CommonLogConfigPage(const QString& name, Config::Log::LOG_KIND kind, QWidget *parent = 0);
    ~CommonLogConfigPage();
    
    QString pageName() const;

protected:
    bool isValid();
    void save();
    void load();
    void loadDefaults();
    void setConfigEnabled(bool value);

private slots:
    void on_ch_disabled_clicked();
    void on_ch_all_clicked();
    void on_ch_tasks_clicked();
    void on_ch_info_clicked();
    void on_ch_warn_clicked();
    void on_ch_err_clicked();
    void on_ch_dbg_clicked();

private:
    void loadLevel(Config::Log::LOG_LEVEL level);
    void checkLevel();
    void setGroupEnabled(bool value);
    void setGroupChecked(bool value);

    Ui::CommonLogConfigPage *ui;
    Config::Log::LOG_KIND m_kind;
    Service::ConfigService::LogConfigService m_service;

    uint m_currentLevel;
};

#endif // COMMON_LOG_CONFIG_PAGE_H

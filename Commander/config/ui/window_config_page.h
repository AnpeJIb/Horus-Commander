#ifndef WINDOW_CONFIG_DIALOG_H
#define WINDOW_CONFIG_DIALOG_H

#include <QWidget>

#include "uiconfig_module.h"
#include "named_page.h"

#include "window_config_service.h"

namespace Ui {
class WindowConfigPage;
}

class WindowConfigPage : public QWidget, public UIConfigModule, public NamedPage
{
    Q_OBJECT
    
public:
    explicit WindowConfigPage(QWidget *parent = 0);
    ~WindowConfigPage();
    
    bool isValid();
    void save();
    void load();
    void loadDefaults();
    void setConfigEnabled(bool value);

    QString pageName() const;

private slots:
    void on_aboutDaemonMode_clicked();

private:
    Ui::WindowConfigPage *ui;
    Service::ConfigService::WindowConfigService m_service;
};

#endif // WINDOW_CONFIG_DIALOG_H

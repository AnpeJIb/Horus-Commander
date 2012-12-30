#ifndef GENERAL_CONFIG_PAGE_H
#define GENERAL_CONFIG_PAGE_H

#include <QWidget>
#include "uiconfig_module.h"
#include "named_page.h"

#include "general_config.h"
#include "general_config_service.h"

namespace Ui {
class GeneralPage;
}

class GeneralConfigPage : public QWidget, public UIConfigModule, public NamedPage
{
    Q_OBJECT
    
public:
    explicit GeneralConfigPage(QWidget *parent = 0);
    ~GeneralConfigPage();
    
    bool isValid();
    void save();
    void load();
    void loadDefaults();
    void setConfigEnabled(bool value);

    QString pageName();

private slots:
    void on_serverPathSearch_clicked();

private:
    void populateLangs();
    void selectLangInBox(QString lang);

    Ui::GeneralPage *ui;

    Service::ConfigService::GeneralConfigService service;
};

#endif // GENERAL_CONFIG_PAGE_H

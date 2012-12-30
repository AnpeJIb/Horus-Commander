#ifndef GENERAL_CONFIG_PAGE_H
#define GENERAL_CONFIG_PAGE_H

#include <QWidget>

#include "uiconfig_module.h"
#include "named_page.h"

#include "general_config.h"
#include "general_config_service.h"

namespace Ui {
class GeneralConfigPage;
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
    void on_dbEdit_clicked();

private:
    void populateBoxes();
    void populateLangs();
    void populateDBs();

    void selectLangInBox(QString lang);
    void selectDBInBox(Config::General::DB_KIND dbKind);

    Config::General::DB_KIND selectedDBkind();

    Ui::GeneralConfigPage *ui;
    Service::ConfigService::GeneralConfigService m_service;
};

#endif // GENERAL_CONFIG_PAGE_H

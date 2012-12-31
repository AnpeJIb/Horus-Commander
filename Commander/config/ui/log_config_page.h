#ifndef LOG_CONFIG_PAGE_H
#define LOG_CONFIG_PAGE_H

#include <QWidget>

#include "uiconfig_module.h"
#include "named_page.h"
#include "listed_stack.h"

namespace Ui {
class LogConfigPage;
}

class LogConfigPage : public QWidget, public UIConfigModule, public NamedPage
{
    Q_OBJECT
    
public:
    explicit LogConfigPage(QWidget *parent = 0);
    ~LogConfigPage();

    QString pageName() const;

protected:
    bool isValid();
    void save();
    void load();
    void loadDefaults();
    void setConfigEnabled(bool value);

private:
    void addListedStack();
    void addPages();

    Ui::LogConfigPage *ui;
    ListedStack* listedStack;
};

#endif // LOG_CONFIG_PAGE_H

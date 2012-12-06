#ifndef NET_PAGE_H
#define NET_PAGE_H

#include <QWidget>

#include "named_page.h"
#include "uiconfig_module.h"

namespace Ui {
class NetPage;
}

class NetPage : public QWidget, public NamedPage, public UIConfigModule
{
    Q_OBJECT
    
public:
    explicit NetPage(QWidget *parent = 0);
    ~NetPage();
    
    QString pageName();

    bool save();
    void load();
    void loadDefaults();

private slots:
    void on_ChannelsCount_valueChanged(int value);

private:
    Ui::NetPage *ui;
};

#endif // NET_PAGE_H

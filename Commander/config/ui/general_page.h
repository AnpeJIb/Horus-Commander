#ifndef GENERALPAGE_H
#define GENERALPAGE_H

#include <QWidget>
#include "uiconfig_module.h"
#include "named_page.h"

namespace Ui {
class GeneralPage;
}

class GeneralPage : public QWidget, public UIConfigModule, public NamedPage
{
    Q_OBJECT
    
public:
    explicit GeneralPage(QWidget *parent = 0);
    ~GeneralPage();
    
    bool save();
    void load();
    void loadDefaults();

    QString pageName();

private slots:
    void on_serverPathBrowse_clicked();

private:
    void populateLangs();
    void selectLangInBox(QString lang);

    Ui::GeneralPage *ui;
};

#endif // GENERALPAGE_H

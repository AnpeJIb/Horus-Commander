#ifndef PRIMARY_CONFIG_DIALOG_H
#define PRIMARY_CONFIG_DIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QAbstractButton>

#include "uiconfig_module.h"
#include "listed_stack.h"

namespace Ui {
class PrimaryConfigDialog;
}

class PrimaryConfigDialog : public QDialog, public UIConfigModule
{
    Q_OBJECT
    
public:
    explicit PrimaryConfigDialog(QWidget *parent = 0);
    ~PrimaryConfigDialog();

    bool save();
    void load();
    void loadDefaults();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    void addListedStack();
    void addPages();

    Ui::PrimaryConfigDialog *ui;
    ListedStack* listedStack;
};

#endif // PRIMARY_CONFIG_DIALOG_H

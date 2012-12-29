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

    bool isValid();
    void save();
    void load();
    void loadDefaults();
    void setConfigEnabled(bool value);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_schemeCopy_clicked();

    void on_schemeDelete_clicked();

    void on_schemeBox_currentIndexChanged(int index);

    void on_schemeEdit_clicked();

private:
    void addListedStack();
    void addPages();

    void reload();
    void loadSchemes();
    void updateSchemeControlsState();
    void updateSchemeDescription();

    Ui::PrimaryConfigDialog *ui;
    ListedStack* listedStack;
};

#endif // PRIMARY_CONFIG_DIALOG_H

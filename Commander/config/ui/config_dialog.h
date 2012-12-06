#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QListWidgetItem>

#include "uiconfig_module.h"

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog, public UIConfigModule
{
    Q_OBJECT
    
public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();
    
    bool save();
    void load();
    void loadDefaults();

private slots:
    void on_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    void setSplitterPos();
    void addPages();

    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H

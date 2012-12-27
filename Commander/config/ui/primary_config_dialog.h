#ifndef PRIMARY_CONFIG_DIALOG_H
#define PRIMARY_CONFIG_DIALOG_H

#include <QDialog>

namespace Ui {
class PrimaryConfigDialog;
}

class PrimaryConfigDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PrimaryConfigDialog(QWidget *parent = 0);
    ~PrimaryConfigDialog();
    
private slots:
    void on_serverPathSearch_clicked();

private:
    Ui::PrimaryConfigDialog *ui;
};

#endif // PRIMARY_CONFIG_DIALOG_H

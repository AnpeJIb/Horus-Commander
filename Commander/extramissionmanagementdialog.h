#ifndef EXTRAMISSIONMANAGEMENTDIALOG_H
#define EXTRAMISSIONMANAGEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class ExtraMissionManagementDialog;
}

class ExtraMissionManagementDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExtraMissionManagementDialog(QWidget *parent = 0);
    ~ExtraMissionManagementDialog();
    
private slots:
    void on_btnLoad_clicked();

    void on_btnUnload_clicked();

    void on_btnReload_clicked();

    void on_btnRun_clicked();

    void on_btnEnd_clicked();

    void on_btnRerun_clicked();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnRestart_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_btnMLE_clicked();

private:
    Ui::ExtraMissionManagementDialog *ui;
};

#endif // EXTRAMISSIONMANAGEMENTDIALOG_H

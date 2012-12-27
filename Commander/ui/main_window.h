#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>

#include "status_widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onAboutToQuit();
    
    void on_actionQuit_triggered();

    void on_btnStop_clicked();

    void on_btnRestart_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_btnExtra_clicked();

    void on_timeLeft_timeChanged(const QTime &date);

    void on_actionConfigurationPrimary_triggered();

private:
    void initLogger();
    void initWindowState();

    void createTrayIcon();

    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayIconMenu;

    Ui::MainWindow *ui;
    StatusWidget* m_logger;

    QIcon* m_iconStopped;
};

#endif // MAINWINDOW_H

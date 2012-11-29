#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>

#include "statuswidget.h"

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
    
private:
    void initLogger();
    void initWindowState();

    void createActions();
    void createTrayIcon();

    QAction *m_showAction;
    QAction *m_minimizeAction;
    QAction *m_quitAction;

    QSystemTrayIcon *m_trayIcon;
    QMenu *m_trayIconMenu;

    Ui::MainWindow *ui;
    StatusWidget* m_logger;

    QIcon* m_iconStopped;
};

#endif // MAINWINDOW_H

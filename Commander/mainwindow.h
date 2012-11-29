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

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    
private:
    void initLogger();

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

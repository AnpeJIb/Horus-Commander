#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "logs.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_iconStopped(new QIcon(":/img/logo.png"))
{
    ui->setupUi(this);
    initLogger();
    createActions();
    createTrayIcon();
    initWindowState();

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLogger()
{
    m_logger = new StatusWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_logger);
    ui->tLog->setLayout(layout);

    LOGS::SET_GUI_LOGGER(m_logger);
    LOGS::UPDATE_GUI_LOGGER();
}

void MainWindow::initWindowState()
{
    QRect geom = CONFIG::WINDOW.geometry();

    if ((geom.x()>=0) && (geom.y()>=0))
    {
        setGeometry(geom);
    } else {
        setGeometry(QStyle::alignedRect(
                        Qt::LeftToRight,
                        Qt::AlignCenter,
                        size(),
                        QApplication::desktop()->availableGeometry()));
    }

    if (CONFIG::WINDOW.isMinimized())
        hide();
    else
        showNormal();
}

void MainWindow::createActions()
{
    m_showAction = new QAction(tr("&Show"), this);
    connect(m_showAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    m_showAction->setIcon(QIcon((":/img/show.png")));

    m_minimizeAction = new QAction(tr("&Minimize"), this);
    connect(m_minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    m_minimizeAction->setIcon(QIcon((":/img/minimize.png")));

    m_quitAction = new QAction(tr("&Quit"), this);
    connect(m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    m_quitAction->setIcon(QIcon((":/img/exit.png")));
}

void MainWindow::createTrayIcon()
{
    m_trayIconMenu = new QMenu(this);
    m_trayIconMenu->addAction(m_showAction);
    m_trayIconMenu->addAction(m_minimizeAction);

    m_trayIconMenu->addSeparator();

    m_trayIconMenu->addAction(m_quitAction);

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setContextMenu(m_trayIconMenu);

    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    m_trayIcon->setIcon(*m_iconStopped);
    m_trayIcon->setVisible(true);
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            if (isVisible()) hide();
            else showNormal();
        default:
            ;
    }
}

void MainWindow::onAboutToQuit()
{
    CONFIG::WINDOW.setGeometry(geometry());
    CONFIG::WINDOW.setMinimized(isMinimized() || (isVisible()==false));
    CONFIG::SAVE();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    disconnect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));
    onAboutToQuit();
}

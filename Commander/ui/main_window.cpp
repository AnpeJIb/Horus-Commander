#include "main_window.h"
#include "ui_main_window.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QCheckBox>

#include "primary_config_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_iconStopped(new QIcon(":/img/logo.png"))
{
    ui->setupUi(this);
    initLogger();
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
}

void MainWindow::initWindowState()
{
    // TODO:
}

void MainWindow::createTrayIcon()
{
    m_trayIconMenu = new QMenu(this);

    m_trayIconMenu->addAction(ui->actionShow);
    m_trayIconMenu->addAction(ui->actionMinimize);
    m_trayIconMenu->addSeparator();
    m_trayIconMenu->addAction(ui->actionConfiguration);
    m_trayIconMenu->addSeparator();
    m_trayIconMenu->addAction(ui->actionQuit);

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
    // TODO:
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    disconnect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));

//    if (CONFIG::WINDOW.promtClose())
//    {
//        QMessageBox msgBox(QMessageBox::Warning,
//                           tr("Closing window"),
//                           tr("Do you wish to quit? Otherwise window will be minimized to tray"), 0, this);
//        QCheckBox dontPrompt(tr("Do not prompt again"), &msgBox);
//        dontPrompt.blockSignals(true);

//        msgBox.addButton(&dontPrompt, QMessageBox::ActionRole);
//        msgBox.addButton(QMessageBox::Yes);
//        msgBox.addButton(QMessageBox::No);

//        int res = msgBox.exec();

//        CONFIG::WINDOW.setPromtClose(dontPrompt.isChecked()==false);
//        CONFIG::WINDOW.setQuitOnClose(res == 16384);
//    }

//    if (CONFIG::WINDOW.quitOnClose())
//        qApp->quit();

    onAboutToQuit();
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_timeLeft_timeChanged(const QTime &date)
{
    Q_UNUSED(date)
    // TODO:
}

void MainWindow::on_actionConfigurationPrimary_triggered()
{
    PrimaryConfigDialog d;
    d.exec();
}

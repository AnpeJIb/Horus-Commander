#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "logs.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QCheckBox>

#include "extramissionmanagementdialog.h"

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

void MainWindow::createTrayIcon()
{
    m_trayIconMenu = new QMenu(this);

    m_trayIconMenu->addAction(ui->actionShow);
    m_trayIconMenu->addAction(ui->actionMinimize);
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
    CONFIG::WINDOW.setGeometry(geometry());
    CONFIG::WINDOW.setMinimized(isMinimized() || (isVisible()==false));
    CONFIG::SAVE();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    disconnect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));

    if (CONFIG::WINDOW.promtClose())
    {
        QMessageBox msgBox(QMessageBox::Warning,
                           tr("Closing window"),
                           tr("Do you wish to quit? Otherwise window will be minimized to tray"), 0, this);
        QCheckBox dontPrompt(tr("Do not prompt again"), &msgBox);
        dontPrompt.blockSignals(true);

        msgBox.addButton(&dontPrompt, QMessageBox::ActionRole);
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);

        int res = msgBox.exec();

        CONFIG::WINDOW.setPromtClose(dontPrompt.isChecked()==false);
        CONFIG::WINDOW.setQuitOnClose(res == 16384);
    }

    if (CONFIG::WINDOW.quitOnClose())
        qApp->quit();

    onAboutToQuit();
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_btnStart_clicked()
{
    // TODO:
}

void MainWindow::on_btnStop_clicked()
{
    // TODO:
}

void MainWindow::on_btnRestart_clicked()
{
    // TODO:
}

void MainWindow::on_btnPrevious_clicked()
{
    // TODO:
}

void MainWindow::on_btnNext_clicked()
{
    // TODO:
}

void MainWindow::on_btnExtra_clicked()
{
    ExtraMissionManagementDialog d;
    d.exec();
}

void MainWindow::on_timeLeft_timeChanged(const QTime &date)
{
    // TODO:
}

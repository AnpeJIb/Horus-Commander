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
    QRect geom = m_winService.geometry();

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

    if (m_winService.isMinimized() || m_winService.startMinimized())
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
    m_winService.setGeometry(geometry());
    m_winService.setMinimized(isMinimized() || (isVisible()==false));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    disconnect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));

    if (m_winService.askQuitConfirmation())
    {
        QMessageBox msgBox(QMessageBox::Warning,
                           tr("Closing window"),
                           tr("Do you wish to quit? Otherwise window will be minimized to tray"), 0, this);
        QCheckBox dontAsk(tr("Do not ask again"), &msgBox);
        dontAsk.blockSignals(true);

        msgBox.addButton(&dontAsk, QMessageBox::ActionRole);
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);

        int res = msgBox.exec();

        m_winService.setAskQuitConfirmation(dontAsk.isChecked()==false);
        m_winService.setQuitOnClose(res == 16384);
    }

    if (m_winService.quitOnClose())
        qApp->quit();

    onAboutToQuit();
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionConfigurationPrimary_triggered()
{
    PrimaryConfigDialog d;
    d.exec();
}

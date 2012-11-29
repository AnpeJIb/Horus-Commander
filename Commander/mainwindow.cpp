#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "logs.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initLogger();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLogger()
{
    logger = new StatusWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(logger);
    ui->tLog->setLayout(layout);

    LOGS::SET_GUI_LOGGER(logger);
    LOGS::UPDATE_GUI_LOGGER();
}

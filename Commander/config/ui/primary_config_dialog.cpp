#include "primary_config_dialog.h"
#include "ui_primary_config_dialog.h"

#include <QFileDialog>

PrimaryConfigDialog::PrimaryConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrimaryConfigDialog)
{
    ui->setupUi(this);
}

PrimaryConfigDialog::~PrimaryConfigDialog()
{
    delete ui;
}

void PrimaryConfigDialog::on_serverPathSearch_clicked()
{
    QString currentPath = ui->serverPath->text();
    QString startDir = (currentPath.isEmpty())?"./":currentPath;

    QString path = QFileDialog::getExistingDirectory(
                this,
                tr("Select server directory"),
                startDir,
                QFileDialog::ShowDirsOnly);

    if (path.isNull() | path.isEmpty()) return;

    ui->serverPath->setText(path);
}

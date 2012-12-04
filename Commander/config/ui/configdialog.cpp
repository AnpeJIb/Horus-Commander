#include "configdialog.h"
#include "ui_configdialog.h"
#include "config.h"
#include "generalpage.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    setSplitterPos();
    addPages();
    load();
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::setSplitterPos()
{
    QList<int> sizes;
    int listW = qMin((width()*20)/100, 140);
    sizes << listW;
    sizes << width()-listW;
    ui->splitter->setSizes(sizes);
}

void ConfigDialog::addPages()
{
    GeneralPage* general = new GeneralPage;
    new QListWidgetItem(
                QIcon(":/img/general.png"),
                general->pageName(),
                ui->list,
                QListWidgetItem::UserType);
    ui->stack->addWidget(general);
    addChild(general);
}

void ConfigDialog::on_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    ui->stack->setCurrentIndex(ui->list->row(current));
}

void ConfigDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->buttonRole(button))
    {
        case QDialogButtonBox::ResetRole:
            loadDefaults();
            break;
        case QDialogButtonBox::RejectRole:
            close();
            break;
        case QDialogButtonBox::AcceptRole:
            if (save())
                accept();
            break;
        default:;
    }
}

bool ConfigDialog::save()
{
    bool result =  saveChildren();

    if (result)
        CONFIG::SAVE();

    return result;
}

void ConfigDialog::load()
{
    loadChildren();
}

void ConfigDialog::loadDefaults()
{
    loadChildrenDefaults();
}

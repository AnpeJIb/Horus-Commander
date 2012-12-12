#include "config_dialog.h"
#include "ui_config_dialog.h"
#include "config.h"
#include "general_page.h"
#include "net_page.h"
#include "difficulty_page.h"

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

    NetPage* net = new NetPage;
    new QListWidgetItem(
                QIcon(":/img/net.png"),
                net->pageName(),
                ui->list,
                QListWidgetItem::UserType);
    ui->stack->addWidget(net);
    addChild(net);

    DifficultyPage* diff = new DifficultyPage;
    new QListWidgetItem(
                QIcon(":/img/diff.png"),
                diff->pageName(),
                ui->list,
                QListWidgetItem::UserType);
    ui->stack->addWidget(diff);
    addChild(diff);
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

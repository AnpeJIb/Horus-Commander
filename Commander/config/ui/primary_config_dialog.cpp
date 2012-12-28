#include "primary_config_dialog.h"
#include "ui_primary_config_dialog.h"

#include "general_page.h"

PrimaryConfigDialog::PrimaryConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrimaryConfigDialog)
{
    ui->setupUi(this);
    addListedStack();
    addPages();
}

PrimaryConfigDialog::~PrimaryConfigDialog()
{
    delete ui;
}

bool PrimaryConfigDialog::save()
{
    bool result =  saveChildren();

//    if (result)
//        CONFIG::SAVE();

    return result;
}

void PrimaryConfigDialog::load()
{
    // load sheme
    loadChildren();
}

void PrimaryConfigDialog::loadDefaults()
{
    loadChildrenDefaults();
}

void PrimaryConfigDialog::addListedStack()
{
    listedStack = new ListedStack(30, 150, this);
    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(listedStack);
    ui->stackedListHolder->setLayout(l);
}

void PrimaryConfigDialog::addPages()
{
    GeneralPage* general = new GeneralPage;
    listedStack->addPage(general->pageName(), QIcon(":/img/general.png"), general);
    addChild(general);

    listedStack->setCurrentIndex(0);
}

void PrimaryConfigDialog::on_buttonBox_clicked(QAbstractButton *button)
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

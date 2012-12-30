#include "primary_config_dialog.h"
#include "ui_primary_config_dialog.h"

#include <QVariant>

#include "general_config_page.h"
#include "window_config_page.h"

#include "primary_config_service.h"
#include "scheme.h"
#include "scheme_editor.h"

using namespace Service::ConfigService;
using namespace Domain::Parameters;

PrimaryConfigDialog::PrimaryConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrimaryConfigDialog)
{
    ui->setupUi(this);
    addListedStack();
    addPages();
    reload();
}

PrimaryConfigDialog::~PrimaryConfigDialog()
{
    delete ui;
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
    GeneralConfigPage* general = new GeneralConfigPage;
    listedStack->addPage(general->pageName(), QIcon(":/img/general.png"), general);
    addChild(general);

    WindowConfigPage* window = new WindowConfigPage;
    listedStack->addPage(window->pageName(), QIcon(":/img/window.png"), window);
    addChild(window);

    listedStack->setCurrentIndex(0);
}

void PrimaryConfigDialog::reload()
{
    loadSchemes();
    load();
}

void PrimaryConfigDialog::loadSchemes()
{
    ui->schemeBox->clear();
    ui->schemeDescr->setText(tr("Scheme description"));
    setConfigEnabled(false);

    QList<Scheme*> lst;
    PrimaryConfigService::schemes(&lst);

    if (lst.count() == 0) return;

    Scheme* current = PrimaryConfigService::currentScheme();

    foreach (Scheme* sch, lst)
    {
        ui->schemeBox->addItem(sch->title, qVariantFromValue((void *) sch));
    }

    int index = ui->schemeBox->findData(qVariantFromValue((void *) current));
    if (index != -1)
    {
       ui->schemeBox->setCurrentIndex(index);
       ui->schemeDescr->setText(current->description);
       setConfigEnabled(true);
    }
}

void PrimaryConfigDialog::load()
{
    updateSchemeDescription();
    loadChildren();
}

void PrimaryConfigDialog::loadDefaults()
{
    loadChildrenDefaults();
}

void PrimaryConfigDialog::setConfigEnabled(bool value)
{
    ui->schemeBox->setEnabled(value);
    ui->schemeDescr->setEnabled(value);
    updateSchemeControlsState();

    setConfigChildrenEnabled(value);
}

void PrimaryConfigDialog::updateSchemeControlsState()
{
    switch (ui->schemeBox->count())
    {
    case 0:
        ui->schemeCopy->setEnabled(false);
        ui->schemeEdit->setEnabled(false);
        ui->schemeDelete->setEnabled(false);
        break;
    case 1:
        ui->schemeCopy->setEnabled(true);
        ui->schemeEdit->setEnabled(true);
        ui->schemeDelete->setEnabled(false);
        break;
    default:
        ui->schemeCopy->setEnabled(true);
        ui->schemeEdit->setEnabled(true);
        ui->schemeDelete->setEnabled(true);
        break;
    }
}

void PrimaryConfigDialog::updateSchemeDescription()
{
    Scheme* sch = PrimaryConfigService::currentScheme();
    if (sch != NULL)
    {
        ui->schemeDescr->setText(sch->description);
    }
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
            if (isValid())
            {
                save();
                accept();
            }
            break;
        default:;
    }
}

bool PrimaryConfigDialog::isValid()
{
    return areChildrenValid();
}

void PrimaryConfigDialog::save()
{
    saveChildren();
}

void PrimaryConfigDialog::on_schemeCopy_clicked()
{
    PrimaryConfigService::copyCurrentSchemeAndSelect();
    reload();
}

void PrimaryConfigDialog::on_schemeDelete_clicked()
{
    PrimaryConfigService::removeCurrentScheme();
    reload();
}

void PrimaryConfigDialog::on_schemeBox_currentIndexChanged(int index)
{
    Scheme* sch = (Scheme*) (ui->schemeBox->itemData(index).value<void *>());
    if (sch == NULL) return;
    PrimaryConfigService::selectCurrentScheme(sch->id);
    load();
}

void PrimaryConfigDialog::on_schemeEdit_clicked()
{
    SchemeJudge* judge = PrimaryConfigService::newSchemeJudge();

    SchemeEditor editor(PrimaryConfigService::currentScheme(), judge);
    int result = editor.exec();

    delete judge;

    if (result==QDialog::Accepted)
    {
        PrimaryConfigService::updateCurrentScheme();
        ui->schemeBox->setItemText(ui->schemeBox->currentIndex(), PrimaryConfigService::currentScheme()->title);
        updateSchemeDescription();
    }
}

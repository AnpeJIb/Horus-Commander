#include "difficulty_page.h"
#include "ui_difficulty_page.h"

#include "difficulty_flight_model_page.h"
#include "difficulty_weapons_page.h"
#include "difficulty_view_page.h"
#include "difficulty_map_icons_page.h"
#include "difficulty_var_page.h"

DifficultyPage::DifficultyPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DifficultyPage)
{
    ui->setupUi(this);
    setSplitterPos();
    addPages();
    load();
}

DifficultyPage::~DifficultyPage()
{
    delete ui;
}

bool DifficultyPage::save()
{
    return saveChildren();
}

void DifficultyPage::load()
{
    return loadChildren();
}

void DifficultyPage::loadDefaults()
{
    return loadChildrenDefaults();
}

QString DifficultyPage::pageName()
{
    return ui->pageName->text();
}

void DifficultyPage::setSplitterPos()
{
    QList<int> sizes;
    int listW = qMin((width()*20)/100, 140);
    sizes << listW;
    sizes << width()-listW;
    ui->splitter->setSizes(sizes);
}

void DifficultyPage::addPages()
{
    DifficultyFlightModelPage* fm = new DifficultyFlightModelPage;
    new QListWidgetItem(
                tr("Flight model"),
                ui->list,
                QListWidgetItem::UserType);
    ui->stack->addWidget(fm);
    subpages << fm;

    DifficultyWeaponsPage* wpn = new DifficultyWeaponsPage;
    new QListWidgetItem(
                tr("Weapons"),
                ui->list,
                QListWidgetItem::UserType);
    ui->stack->addWidget(wpn);
    subpages << wpn;

    DifficultyViewPage* vw = new DifficultyViewPage;
    new QListWidgetItem(
                tr("View"),
                ui->list,
                QListWidgetItem::UserType);
    ui->stack->addWidget(vw);
    subpages << vw;

    DifficultyMapIconsPage* mi = new DifficultyMapIconsPage;
    new QListWidgetItem(
                tr("Map & icons"),
                ui->list,
                QListWidgetItem::UserType);
    ui->stack->addWidget(mi);
    subpages << mi;

    DifficultyVarPage* var = new DifficultyVarPage;
    new QListWidgetItem(
                tr("Various"),
                ui->list,
                QListWidgetItem::UserType);
    ui->stack->addWidget(var);
    subpages << var;

    ui->stack->setCurrentIndex(0);
    ui->list->setCurrentRow(0);
}

void DifficultyPage::on_easyButton_clicked()
{

}

void DifficultyPage::on_normalButton_clicked()
{

}

void DifficultyPage::on_realButton_clicked()
{

}

void DifficultyPage::on_list_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    ui->stack->setCurrentIndex(ui->list->row(current));
}

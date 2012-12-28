#include "listed_stack.h"
#include "ui_listed_stack.h"

ListedStack::ListedStack(int percentPos, int minPos, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ListedStack)
{
    ui->setupUi(this);
    setSplitterPosition(percentPos, minPos);
}

ListedStack::~ListedStack()
{
    delete ui;
}

void ListedStack::addPage(const QString &name, const QIcon &icon, QWidget *page)
{
    new QListWidgetItem(
                icon,
                name,
                ui->list,
                QListWidgetItem::UserType);
    ui->stack->addWidget(page);
}

void ListedStack::setCurrentIndex(int value)
{
    ui->list->setCurrentRow(value);
}

void ListedStack::on_list_currentRowChanged(int currentRow)
{
    if (currentRow < 0) return;
    if (currentRow > ui->stack->count()-1) return;

    ui->stack->setCurrentIndex(currentRow);
}

void ListedStack::setSplitterPosition(int percent, int min)
{
    QList<int> sizes;
    int listW = qMin((width()*percent)/100, min);
    sizes << listW;
    sizes << width()-listW;
    ui->splitter->setSizes(sizes);
}

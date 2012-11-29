#include "statuswidget.h"
#include <QTime>
#include <QHeaderView>

StatusWidget::StatusWidget()
    : last(NULL),
      iconBuzy(new QIcon(":/img/bullet_yellow.png")),
      iconDone(new QIcon(":/img/bullet_green.png")),
      iconFail(new QIcon(":/img/bullet_red.png")),
      iconDbg(new QIcon(":/img/bullet_grey.png")),
      iconInfo(new QIcon(":/img/bullet_blue.png")),
      iconWarn(new QIcon(":/img/bullet_orange.png")),
      iconErr(new QIcon(":/img/bullet_red.png"))
{
    QStringList headerNames;
    headerNames.append(tr("Message"));
    headerNames.append(tr("Time"));
    setHeaderLabels(headerNames);

    setLevel(StatusPrinter::ALL);
    header()->resizeSection(0, width()-200);
}

void StatusWidget::statusNew(QString str)
{
    if ((level & StatusPrinter::TASKS)==0) return;

    QTreeWidgetItem* item;

    if ((last==NULL)
    || ((last->parent()==NULL)
        && ((StatusWidget::NodeType)(last->data(0, Qt::UserRole).toInt())==StatusWidget::TASK_FINISHED)))

        item = new QTreeWidgetItem(this);
    else
        item = new QTreeWidgetItem(last);

    item->setText(0, str);
    item->setText(1, QTime::currentTime().toString());
    item->setData(0, Qt::UserRole, QVariant(StatusWidget::TASK_NEW));
    item->setData(1, Qt::UserRole, QVariant(0)); // msg count
    item->setExpanded(true);

    last = item;
    last->setIcon(0, *iconBuzy);
}

void StatusWidget::statusDone() {statusFinish(iconDone);}
void StatusWidget::statusFail() {statusFinish(iconFail);}

void StatusWidget::statusFinish(QIcon *icon)
{
    if (((level & StatusPrinter::TASKS)==0) || (last==NULL)) return;

    if (last->data(1, Qt::UserRole).toInt()==0) // no messages
        last->setExpanded(false);

    last->setIcon(0, *icon);
    last->setData(0, Qt::UserRole, QVariant(StatusWidget::TASK_FINISHED));
    last = last->parent();
}

void StatusWidget::msgDebug(QString str)
{
    if ((level & StatusPrinter::DEBUG)==0) return;
    msg(str, iconDbg);
}

void StatusWidget::msgInfo(QString str)
{
    if ((level & StatusPrinter::INFO)==0) return;
    msg(str, iconInfo);
}

void StatusWidget::msgWarn(QString str)
{
    if ((level & StatusPrinter::WARNING)==0) return;
    msg(str, iconWarn);
}

void StatusWidget::msgError(QString str)
{
    if ((level & StatusPrinter::ERROR)==0) return;
    msg(str, iconErr);
}

void StatusWidget::msg(const QString &str, QIcon *icon)
{
    QTreeWidgetItem* item;

    if (last==NULL)
        item = new QTreeWidgetItem(this);
    else
        item = new QTreeWidgetItem(last);

    item->setText(0, str);
    item->setText(1, QTime::currentTime().toString());
    item->setData(0, Qt::UserRole, QVariant(StatusWidget::MSG));
    item->setIcon(0, *icon);

    QTreeWidgetItem* curr;
    int msgCnt;

    for(curr=last; curr!=NULL; curr = curr->parent())
    {
        msgCnt = curr->data(1, Qt::UserRole).toInt();
        curr->setData(1, Qt::UserRole, QVariant(msgCnt+1));
    }
}

void StatusWidget::clearAll()
{
    clear();
    last = NULL;
}

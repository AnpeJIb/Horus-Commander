#include "logger_tree_widget.h"

#include <QTime>
#include <QHeaderView>

#include "log_config.h"
#include "bitwise.h"

LoggerTreeWidget::LoggerTreeWidget()
    : Logger(Config::Log::LOG_GUI),
      last(NULL),
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

    setLevel(Config::Log::LEVEL_ALL);

    header()->setStretchLastSection(false);
    header()->setResizeMode(0, QHeaderView::Stretch);
    header()->setResizeMode(1, QHeaderView::Fixed);
    header()->resizeSection(1, 120);
}

void LoggerTreeWidget::taskNew(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_TASKS)==0) return;

    QTreeWidgetItem* item;

    if ((last==NULL)
    || ((last->parent()==NULL)
        && ((LoggerTreeWidget::NodeType)(last->data(0, Qt::UserRole).toInt())==LoggerTreeWidget::TASK_FINISHED)))

        item = new QTreeWidgetItem(this);
    else
        item = new QTreeWidgetItem(last);

    item->setText(0, str);
    item->setText(1, QTime::currentTime().toString());
    item->setData(0, Qt::UserRole, QVariant(LoggerTreeWidget::TASK_NEW));
    item->setData(1, Qt::UserRole, QVariant(0)); // msg count
    item->setExpanded(true);

    last = item;
    last->setIcon(0, *iconBuzy);
}

void LoggerTreeWidget::taskDone() {statusFinish(iconDone);}
void LoggerTreeWidget::taskFail() {statusFinish(iconFail);}

void LoggerTreeWidget::statusFinish(QIcon *icon)
{
    if ((BIT_CHECK_RAW(level, Config::Log::LEVEL_TASKS)==0) || (last==NULL)) return;

    if (last->data(1, Qt::UserRole).toInt()==0) // no messages
        last->setExpanded(false);

    last->setIcon(0, *icon);
    last->setData(0, Qt::UserRole, QVariant(LoggerTreeWidget::TASK_FINISHED));
    last = last->parent();
}

void LoggerTreeWidget::msgDebug(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_DEBUG)==0) return;
    msg(str, iconDbg);
}

void LoggerTreeWidget::msgInfo(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_INFO)==0) return;
    msg(str, iconInfo);
}

void LoggerTreeWidget::msgWarning(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_WARNING)==0) return;
    msg(str, iconWarn);
}

void LoggerTreeWidget::msgError(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_ERROR)==0) return;
    msg(str, iconErr);
}

void LoggerTreeWidget::msg(const QString &str, QIcon *icon)
{
    QTreeWidgetItem* item;

    if (last==NULL)
        item = new QTreeWidgetItem(this);
    else
        item = new QTreeWidgetItem(last);

    item->setText(0, str);
    item->setText(1, QTime::currentTime().toString());
    item->setData(0, Qt::UserRole, QVariant(LoggerTreeWidget::MSG));
    item->setIcon(0, *icon);

    QTreeWidgetItem* curr;
    int msgCnt;

    for(curr=last; curr!=NULL; curr = curr->parent())
    {
        msgCnt = curr->data(1, Qt::UserRole).toInt();
        curr->setData(1, Qt::UserRole, QVariant(msgCnt+1));
    }
}

void LoggerTreeWidget::clearAll()
{
    clear();
    last = NULL;
}

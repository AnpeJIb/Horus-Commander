#ifndef LOGGER_LOGGER_TREE_WIDGET_H
#define LOGGER_LOGGER_TREE_WIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QIcon>
#include "logger.h"

namespace Ui {
class StatusWidget;
}

class LoggerTreeWidget : public QTreeWidget, public Logger
{
    Q_OBJECT

private:
    enum NodeType
    {
        TASK_NEW,
        TASK_FINISHED,
        MSG
    };

public:
    LoggerTreeWidget();

public slots:
    void taskNew(QString str);
    void taskDone();
    void taskFail();

    void msgDebug(QString str);
    void msgInfo(QString str);
    void msgWarning(QString str);
    void msgError(QString str);

    void clearAll();

private:
    void statusFinish(QIcon* icon);
    void msg(const QString& str, QIcon* icon);

    Ui::StatusWidget *ui;
    QTreeWidgetItem* last;

    QIcon* iconBuzy;
    QIcon* iconDone;
    QIcon* iconFail;
    QIcon* iconDbg;
    QIcon* iconInfo;
    QIcon* iconWarn;
    QIcon* iconErr;
};

#endif // LOGGER_LOGGER_TREE_WIDGET_H

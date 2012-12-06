#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QIcon>
#include "status_print.h"

namespace Ui {
class StatusWidget;
}

class StatusWidget : public QTreeWidget, public StatusPrinter
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
    StatusWidget();

public slots:
    void statusNew(QString str);
    void statusDone();
    void statusFail();

    void msgDebug(QString str);
    void msgInfo(QString str);
    void msgWarn(QString str);
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

#endif // STATUSWIDGET_H

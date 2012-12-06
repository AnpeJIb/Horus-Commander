#ifndef FOOSTATUSPRINTER_H
#define FOOSTATUSPRINTER_H

#include <QObject>
#include "status_print.h"

class FooStatusPrinter : public QObject, public StatusPrinter
{
    Q_OBJECT
public:
    explicit FooStatusPrinter();

public slots:
    void statusNew(QString str);
    void statusDone();
    void statusFail();

    void msgDebug(QString str);
    void msgInfo(QString str);
    void msgWarn(QString str);
    void msgError(QString str);
};

#endif // FOOSTATUSPRINTER_H

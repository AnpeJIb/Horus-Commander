#ifndef LOGGER_FOO_LOGGER_H
#define LOGGER_FOO_LOGGER_H

#include <QObject>
#include "logger.h"

class FooLogger : public QObject, public Logger
{
    Q_OBJECT
public:
    explicit FooLogger();

public slots:
    void taskNew(QString str);
    void taskDone();
    void taskFail();

    void msgDebug(QString str);
    void msgInfo(QString str);
    void msgWarning(QString str);
    void msgError(QString str);
};

#endif // LOGGER_FOO_LOGGER_H

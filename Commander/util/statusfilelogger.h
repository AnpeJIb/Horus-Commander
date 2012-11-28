#ifndef STATUSFILELOGGER_H
#define STATUSFILELOGGER_H

#include "statusprint.h"
#include <QFile>
#include <QTextStream>
#include <QStack>

class StatusFileLogger : public StatusPrinter
{
    Q_OBJECT
public:
    StatusFileLogger(QString filename);
    ~StatusFileLogger();

public slots:
    void statusNew(QString str);
    void statusDone();
    void statusFail();

    void msgInfo(QString str);
    void msgWarn(QString str);
    void msgErr(QString str);

private:
    void printStr(const QString& prefix, const QString& str);

    QFile* file;
    QTextStream* stream;
    QStack<QString> stack;
};

#endif // STATUSFILELOGGER_H

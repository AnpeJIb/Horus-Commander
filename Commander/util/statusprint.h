#ifndef PRINTSTATUS_H
#define PRINTSTATUS_H

#include <QObject>
#include <QString>
#include <QList>

class StatusPrinter;

class StatusPrinter : public QObject
{
public:
    enum Level
    {
        ALL     = (1 << 0),
        TASKS   = (1 << 1),
        INFO    = (1 << 2),
        WARNING = (1 << 3),
        ERROR   = (1 << 4),
        NONE    = (1 << 5)
    };

public slots:
    virtual void statusNew(QString str) = 0;
    virtual void statusDone() = 0;
    virtual void statusFail() = 0;

    virtual void msgInfo(QString str) = 0;
    virtual void msgWarn(QString str) = 0;
    virtual void msgErr(QString str) = 0;

public:
    void setLevel(quint8 value){this->level = (value==ALL)?0x3F:value;}

protected:
    quint8 level;
};

class STATUS_PRINT
{
public:
    static void REGISTER(StatusPrinter* printer);
    static void UNREGISTER(StatusPrinter* printer);

    static void NEW(const QString& str);
    static void DONE();
    static void FAIL();

    static void INFO(const QString& str);
    static void WARN(const QString& str);
    static void ERR(const QString& str);

private:
    static QList<StatusPrinter*> printers;
};

#endif // PRINTSTATUS_H

#ifndef PRINTSTATUS_H
#define PRINTSTATUS_H

#include <QString>
#include <QList>

class StatusPrinter
{
public:
    enum Level
    {
        ALL     = (1 << 0),
        TASKS   = (1 << 1),
        DEBUG   = (1 << 2),
        INFO    = (1 << 3),
        WARNING = (1 << 4),
        ERROR   = (1 << 5),
        NONE    = (1 << 6)
    };

public:
    virtual void statusNew(QString str) = 0;
    virtual void statusDone() = 0;
    virtual void statusFail() = 0;

    virtual void msgDebug(QString str) = 0;
    virtual void msgInfo(QString str) = 0;
    virtual void msgWarn(QString str) = 0;
    virtual void msgError(QString str) = 0;

    void setLevel(quint8 value){this->level = (value==ALL)?0x7F:value;}

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

    static void DEBUG(const QString& str);
    static void INFO(const QString& str);
    static void WARN(const QString& str);
    static void ERROR(const QString& str);

private:
    static QList<StatusPrinter*> printers;
};

#endif // PRINTSTATUS_H

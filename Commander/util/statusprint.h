#ifndef PRINTSTATUS_H
#define PRINTSTATUS_H

#include <QString>
#include <QList>

class StatusPrinter
{
public:
    enum Level
    {
        LEVEL_ALL     = (1 << 0),
        LEVEL_TASKS   = (1 << 1),
        LEVEL_DEBUG   = (1 << 2),
        LEVEL_INFO    = (1 << 3),
        LEVEL_WARNING = (1 << 4),
        LEVEL_ERROR   = (1 << 5),
        LEVEL_NONE    = (1 << 6)
    };

public:
    virtual void statusNew(QString str) = 0;
    virtual void statusDone() = 0;
    virtual void statusFail() = 0;

    virtual void msgDebug(QString str) = 0;
    virtual void msgInfo(QString str) = 0;
    virtual void msgWarn(QString str) = 0;
    virtual void msgError(QString str) = 0;

    void setLevel(quint8 value){this->level = (value==LEVEL_ALL)?0x7F:value;}

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

    static void DEBUG_(const QString& str);
    static void INFO_ (const QString& str);
    static void WARN_ (const QString& str);
    static void ERROR_(const QString& str);

private:
    static QList<StatusPrinter*> printers;
};

#endif // PRINTSTATUS_H

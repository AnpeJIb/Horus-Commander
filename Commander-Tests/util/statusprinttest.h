#ifndef STATUSPRINTTEST_H
#define STATUSPRINTTEST_H

#include <QObject>
#include "statusprint.h"

class FooStatusPrinter;

class FooStatusPrinter : public StatusPrinter
{
    Q_OBJECT
public:
    explicit FooStatusPrinter();

public slots:
    void statusNew(QString str);
    void statusDone();
    void statusFail();

    void msgInfo(QString str);
    void msgWarn(QString str);
    void msgErr(QString str);
};

class StatusPrintTest : public QObject
{
    Q_OBJECT
public:
    explicit StatusPrintTest(QObject *parent = 0);
    ~StatusPrintTest();
    
private slots:
    void testLevelNone();
    void testLevelTasks();
    void testLevelInfo();
    void testLevelWarn();
    void testLevelErr();
    void testLevelAll();

    void testLevelTaskAndInfo();
    void testLevelTaskAndWarn();
    void testLevelTaskAndErr();

private:
    void init();
    void clearUp();

    void testAll(quint8 level);
    void testStatusDone();
    void testStatusFail();
    void testMsg();

    FooStatusPrinter printer;
};

#endif // STATUSPRINTTEST_H

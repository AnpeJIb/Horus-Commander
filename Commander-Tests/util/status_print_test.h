#ifndef STATUSPRINTTEST_H
#define STATUSPRINTTEST_H

#include <QObject>
#include "status_print.h"
#include "status_tester.h"
#include "foo_status_printer.h"

class StatusPrintTest : public QObject, public StatusTester
{
    Q_OBJECT
public:
    explicit StatusPrintTest(QObject *parent = 0);
    
protected:
    StatusPrinter* getPrinter();

private slots:
    void initTestCase();
    void testLevelNone();
    void testLevelTasks();
    void testLevelDebug();
    void testLevelInfo();
    void testLevelWarn();
    void testLevelErr();
    void testLevelAll();

    void testLevelTaskAndDebug();
    void testLevelTaskAndInfo();
    void testLevelTaskAndWarn();
    void testLevelTaskAndErr();
    void cleanupTestCase();

private:
    FooStatusPrinter printer;
};

#endif // STATUSPRINTTEST_H

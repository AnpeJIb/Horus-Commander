#ifndef STATUSFILELOGGERTEST_H
#define STATUSFILELOGGERTEST_H

#include <QObject>
#include "statusfilelogger.h"
#include "statustester.h"

class StatusFileLoggerTest: public QObject, public StatusTester
{
    Q_OBJECT
public:
    explicit StatusFileLoggerTest(QObject *parent = 0);

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
    StatusFileLogger* logger;
    QString filepath;
};

#endif // STATUSFILELOGGERTEST_H

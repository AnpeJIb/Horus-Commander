#include "statusprinttest.h"

#include <iostream>
using namespace std;

FooStatusPrinter::FooStatusPrinter()
{
}

void FooStatusPrinter::statusNew(QString str)
{
    if (level & StatusPrinter::TASKS)
        cout << "New task: " << qPrintable(str) << endl;
}

void FooStatusPrinter::statusDone()
{
    if (level & StatusPrinter::TASKS)
        cout << "Task done" << endl;
}

void FooStatusPrinter::statusFail()
{
    if (level & StatusPrinter::TASKS)
        cout << "Task failed" << endl;
}

void FooStatusPrinter::msgDebug(QString str)
{
    if (level & StatusPrinter::DEBUG)
        cout << "DBG : " << qPrintable(str) << endl;
}

void FooStatusPrinter::msgInfo(QString str)
{
    if (level & StatusPrinter::INFO)
        cout << "INFO: " << qPrintable(str) << endl;
}

void FooStatusPrinter::msgWarn(QString str)
{
    if (level & StatusPrinter::WARNING)
        cout << "WARN: " << qPrintable(str) << endl;
}

void FooStatusPrinter::msgError(QString str)
{
    if (level & StatusPrinter::ERROR)
        cout << "ERR : " << qPrintable(str) << endl;
}

StatusPrintTest::StatusPrintTest(QObject *parent) :
    QObject(parent)
{
}

StatusPrinter *StatusPrintTest::getPrinter()
{
    return &printer;
}

void StatusPrintTest::initTestCase()
{
    STATUS_PRINT::REGISTER(&printer);
}

void StatusPrintTest::testLevelNone()   {testAll(StatusPrinter::NONE);}
void StatusPrintTest::testLevelTasks()  {testAll(StatusPrinter::TASKS);}
void StatusPrintTest::testLevelDebug()   {testAll(StatusPrinter::DEBUG);}
void StatusPrintTest::testLevelInfo()   {testAll(StatusPrinter::INFO);}
void StatusPrintTest::testLevelWarn()   {testAll(StatusPrinter::WARNING);}
void StatusPrintTest::testLevelErr()    {testAll(StatusPrinter::ERROR);}
void StatusPrintTest::testLevelAll()    {testAll(StatusPrinter::ALL);}

void StatusPrintTest::testLevelTaskAndDebug() {testAll(StatusPrinter::TASKS | StatusPrinter::DEBUG);}
void StatusPrintTest::testLevelTaskAndInfo() {testAll(StatusPrinter::TASKS | StatusPrinter::INFO);}
void StatusPrintTest::testLevelTaskAndWarn() {testAll(StatusPrinter::TASKS | StatusPrinter::WARNING);}
void StatusPrintTest::testLevelTaskAndErr()  {testAll(StatusPrinter::TASKS | StatusPrinter::ERROR);}

void StatusPrintTest::cleanupTestCase()
{
    STATUS_PRINT::UNREGISTER(&printer);
}

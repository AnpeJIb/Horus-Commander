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

void FooStatusPrinter::msgInfo(QString str)
{
    if (level & StatusPrinter::INFO)
        cout << "Info: " << qPrintable(str) << endl;
}

void FooStatusPrinter::msgWarn(QString str)
{
    if (level & StatusPrinter::WARNING)
        cout << "Warning: " << qPrintable(str) << endl;
}

void FooStatusPrinter::msgErr(QString str)
{
    if (level & StatusPrinter::ERROR)
        cout << "Error: " << qPrintable(str) << endl;
}

StatusPrintTest::StatusPrintTest(QObject *parent) :
    QObject(parent)
{
    init();
}

StatusPrintTest::~StatusPrintTest()
{
    clearUp();
}

void StatusPrintTest::init()
{
    STATUS_PRINT::REGISTER(&printer);
}

void StatusPrintTest::clearUp()
{
    STATUS_PRINT::UNREGISTER(&printer);
}

void StatusPrintTest::testLevelNone()   {testAll(StatusPrinter::NONE);}
void StatusPrintTest::testLevelTasks()  {testAll(StatusPrinter::TASKS);}
void StatusPrintTest::testLevelInfo()   {testAll(StatusPrinter::INFO);}
void StatusPrintTest::testLevelWarn()   {testAll(StatusPrinter::WARNING);}
void StatusPrintTest::testLevelErr()    {testAll(StatusPrinter::ERROR);}
void StatusPrintTest::testLevelAll()    {testAll(StatusPrinter::ALL);}

void StatusPrintTest::testLevelTaskAndInfo() {testAll(StatusPrinter::TASKS | StatusPrinter::INFO);}
void StatusPrintTest::testLevelTaskAndWarn() {testAll(StatusPrinter::TASKS | StatusPrinter::WARNING);}
void StatusPrintTest::testLevelTaskAndErr()  {testAll(StatusPrinter::TASKS | StatusPrinter::ERROR);}

void StatusPrintTest::testAll(quint8 level)
{
    printer.setLevel(level);

    testStatusDone();
    testStatusFail();
    testMsg();
}

void StatusPrintTest::testStatusDone()
{
    STATUS_PRINT::NEW("Task 1");
    STATUS_PRINT::DONE();
}

void StatusPrintTest::testStatusFail()
{
    STATUS_PRINT::NEW("Task 2");
    STATUS_PRINT::FAIL();
}

void StatusPrintTest::testMsg()
{
    STATUS_PRINT::INFO("some information");
    STATUS_PRINT::WARN("some warning");
    STATUS_PRINT::ERR("some error");
}

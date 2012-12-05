#include "foostatusprinter.h"

#include <iostream>
using namespace std;

FooStatusPrinter::FooStatusPrinter()
{
}

void FooStatusPrinter::statusNew(QString str)
{
    if (level & StatusPrinter::LEVEL_TASKS)
        cout << "New task: " << qPrintable(str) << endl;
}

void FooStatusPrinter::statusDone()
{
    if (level & StatusPrinter::LEVEL_TASKS)
        cout << "Task done" << endl;
}

void FooStatusPrinter::statusFail()
{
    if (level & StatusPrinter::LEVEL_TASKS)
        cout << "Task failed" << endl;
}

void FooStatusPrinter::msgDebug(QString str)
{
    if (level & StatusPrinter::LEVEL_DEBUG)
        cout << "DBG : " << qPrintable(str) << endl;
}

void FooStatusPrinter::msgInfo(QString str)
{
    if (level & StatusPrinter::LEVEL_INFO)
        cout << "INFO: " << qPrintable(str) << endl;
}

void FooStatusPrinter::msgWarn(QString str)
{
    if (level & StatusPrinter::LEVEL_WARNING)
        cout << "WARN: " << qPrintable(str) << endl;
}

void FooStatusPrinter::msgError(QString str)
{
    if (level & StatusPrinter::LEVEL_ERROR)
        cout << "ERR : " << qPrintable(str) << endl;
}

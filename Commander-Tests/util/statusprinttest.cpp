#include "statusprinttest.h"

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

void StatusPrintTest::testLevelNone()   {testAll(StatusPrinter::LEVEL_NONE);}
void StatusPrintTest::testLevelTasks()  {testAll(StatusPrinter::LEVEL_TASKS);}
void StatusPrintTest::testLevelDebug()   {testAll(StatusPrinter::LEVEL_DEBUG);}
void StatusPrintTest::testLevelInfo()   {testAll(StatusPrinter::LEVEL_INFO);}
void StatusPrintTest::testLevelWarn()   {testAll(StatusPrinter::LEVEL_WARNING);}
void StatusPrintTest::testLevelErr()    {testAll(StatusPrinter::LEVEL_ERROR);}
void StatusPrintTest::testLevelAll()    {testAll(StatusPrinter::LEVEL_ALL);}

void StatusPrintTest::testLevelTaskAndDebug() {testAll(StatusPrinter::LEVEL_TASKS | StatusPrinter::LEVEL_DEBUG);}
void StatusPrintTest::testLevelTaskAndInfo() {testAll(StatusPrinter::LEVEL_TASKS | StatusPrinter::LEVEL_INFO);}
void StatusPrintTest::testLevelTaskAndWarn() {testAll(StatusPrinter::LEVEL_TASKS | StatusPrinter::LEVEL_WARNING);}
void StatusPrintTest::testLevelTaskAndErr()  {testAll(StatusPrinter::LEVEL_TASKS | StatusPrinter::LEVEL_ERROR);}

void StatusPrintTest::cleanupTestCase()
{
    STATUS_PRINT::UNREGISTER(&printer);
}

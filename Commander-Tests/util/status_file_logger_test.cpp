#include "status_file_logger_test.h"
#include "file_util.h"

#include <QFile>
#include <QFileInfo>

#include <iostream>
using namespace std;

StatusFileLoggerTest::StatusFileLoggerTest(QObject *parent)
    : QObject(parent)
{
}

StatusPrinter* StatusFileLoggerTest::getPrinter()
{
    return logger;
}

void StatusFileLoggerTest::initTestCase()
{
    QFileInfo fileInfo("./test.log");
    filepath = fileInfo.absoluteFilePath();

    logger = new StatusFileLogger(filepath);
    STATUS_PRINT::REGISTER(logger);
}

void StatusFileLoggerTest::testLevelNone()   {testAll(StatusPrinter::LEVEL_NONE);}
void StatusFileLoggerTest::testLevelTasks()  {testAll(StatusPrinter::LEVEL_TASKS);}
void StatusFileLoggerTest::testLevelDebug()   {testAll(StatusPrinter::LEVEL_DEBUG);}
void StatusFileLoggerTest::testLevelInfo()   {testAll(StatusPrinter::LEVEL_INFO);}
void StatusFileLoggerTest::testLevelWarn()   {testAll(StatusPrinter::LEVEL_WARNING);}
void StatusFileLoggerTest::testLevelErr()    {testAll(StatusPrinter::LEVEL_ERROR);}
void StatusFileLoggerTest::testLevelAll()    {testAll(StatusPrinter::LEVEL_ALL);}

void StatusFileLoggerTest::testLevelTaskAndDebug() {testAll(StatusPrinter::LEVEL_TASKS | StatusPrinter::LEVEL_DEBUG);}
void StatusFileLoggerTest::testLevelTaskAndInfo() {testAll(StatusPrinter::LEVEL_TASKS | StatusPrinter::LEVEL_INFO);}
void StatusFileLoggerTest::testLevelTaskAndWarn() {testAll(StatusPrinter::LEVEL_TASKS | StatusPrinter::LEVEL_WARNING);}
void StatusFileLoggerTest::testLevelTaskAndErr()  {testAll(StatusPrinter::LEVEL_TASKS | StatusPrinter::LEVEL_ERROR);}

void StatusFileLoggerTest::cleanupTestCase()
{
    STATUS_PRINT::UNREGISTER(logger);
    delete logger;

    printFile(filepath);
    QFile::remove(filepath);
}

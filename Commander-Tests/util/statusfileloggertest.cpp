#include "statusfileloggertest.h"
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

void StatusFileLoggerTest::testLevelNone()   {testAll(StatusPrinter::NONE);}
void StatusFileLoggerTest::testLevelTasks()  {testAll(StatusPrinter::TASKS);}
void StatusFileLoggerTest::testLevelDebug()   {testAll(StatusPrinter::DEBUG);}
void StatusFileLoggerTest::testLevelInfo()   {testAll(StatusPrinter::INFO);}
void StatusFileLoggerTest::testLevelWarn()   {testAll(StatusPrinter::WARNING);}
void StatusFileLoggerTest::testLevelErr()    {testAll(StatusPrinter::ERROR);}
void StatusFileLoggerTest::testLevelAll()    {testAll(StatusPrinter::ALL);}

void StatusFileLoggerTest::testLevelTaskAndDebug() {testAll(StatusPrinter::TASKS | StatusPrinter::DEBUG);}
void StatusFileLoggerTest::testLevelTaskAndInfo() {testAll(StatusPrinter::TASKS | StatusPrinter::INFO);}
void StatusFileLoggerTest::testLevelTaskAndWarn() {testAll(StatusPrinter::TASKS | StatusPrinter::WARNING);}
void StatusFileLoggerTest::testLevelTaskAndErr()  {testAll(StatusPrinter::TASKS | StatusPrinter::ERROR);}

void StatusFileLoggerTest::cleanupTestCase()
{
    STATUS_PRINT::UNREGISTER(logger);
    delete logger;

    QString cmd;

#ifdef _WIN32_
    cmd = "type";
#else
    cmd = "cat";
#endif
    cmd.append(" \"").append(filepath).append("\"");

    int i = system(cmd.toStdString().c_str());
    Q_UNUSED(i)

    QFile::remove(filepath);
}

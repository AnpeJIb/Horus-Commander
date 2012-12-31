#include "foo_logger.h"

#include "log_config.h"
#include "bitwise.h"

#include <iostream>
using namespace std;

FooLogger::FooLogger()
    : Logger(Config::Log::LOG_NONE)
{
}

void FooLogger::taskNew(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_TASKS))
        cout << "New task: " << qPrintable(str) << endl;
}

void FooLogger::taskDone()
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_TASKS))
        cout << "Task done" << endl;
}

void FooLogger::taskFail()
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_TASKS))
        cout << "Task failed" << endl;
}

void FooLogger::msgDebug(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_DEBUG))
        cout << "DBG : " << qPrintable(str) << endl;
}

void FooLogger::msgInfo(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_INFO))
        cout << "INFO: " << qPrintable(str) << endl;
}

void FooLogger::msgWarning(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_WARNING))
        cout << "WARN: " << qPrintable(str) << endl;
}

void FooLogger::msgError(QString str)
{
    if (BIT_CHECK_RAW(level, Config::Log::LEVEL_ERROR))
        cout << "ERR : " << qPrintable(str) << endl;
}

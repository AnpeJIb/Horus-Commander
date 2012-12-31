#include "logger_tester.h"
#include "log_service.h"

void LoggerTester::testAll(quint8 level)
{
    getLogger()->setLevel(level);

    testStatusDone();
    testStatusFail();
    testMsg();
}

void LoggerTester::testStatusDone()
{
    Service::LOGGER::taskNew("Task 1");
    Service::LOGGER::taskDone();
}

void LoggerTester::testStatusFail()
{
    Service::LOGGER::taskNew("Task 2");
    Service::LOGGER::taskFail();
}

void LoggerTester::testMsg()
{
    Service::LOGGER::msgDebug("some debug");
    Service::LOGGER::msgInfo("some information");
    Service::LOGGER::msgWarning("some warning");
    Service::LOGGER::msgError("some error");
}

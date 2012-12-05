#include "statustester.h"

void StatusTester::testAll(quint8 level)
{
    getPrinter()->setLevel(level);

    testStatusDone();
    testStatusFail();
    testMsg();
}

void StatusTester::testStatusDone()
{
    STATUS_PRINT::NEW("Task 1");
    STATUS_PRINT::DONE();
}

void StatusTester::testStatusFail()
{
    STATUS_PRINT::NEW("Task 2");
    STATUS_PRINT::FAIL();
}

void StatusTester::testMsg()
{
    STATUS_PRINT::DEBUG_("some debug");
    STATUS_PRINT::INFO_("some information");
    STATUS_PRINT::WARN_("some warning");
    STATUS_PRINT::ERROR_("some error");
}

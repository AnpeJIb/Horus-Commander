#ifndef LOGGER_LOGGER_TESTER_H
#define LOGGER_LOGGER_TESTER_H

#include <QObject>
#include "logger.h"

class LoggerTester
{
protected:
    void testAll(quint8 level);
    void testStatusDone();
    void testStatusFail();
    void testMsg();

    virtual Logger* getLogger() = 0;
};

#endif // LOGGER_LOGGER_TESTER_H

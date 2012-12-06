#ifndef STATUSTESTER_H
#define STATUSTESTER_H

#include <QObject>
#include "status_print.h"

class StatusTester
{
protected:
    void testAll(quint8 level);
    void testStatusDone();
    void testStatusFail();
    void testMsg();

    virtual StatusPrinter* getPrinter() = 0;
};

#endif // STATUSTESTER_H

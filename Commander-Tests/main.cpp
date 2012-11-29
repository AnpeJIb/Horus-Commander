#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "footest.h"
#include "statusprinttest.h"
#include "statusfileloggertest.h"
#include "configtest.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTest::qExec(new FooTest, argc, argv);
    QTest::qExec(new StatusPrintTest, argc, argv);
    QTest::qExec(new StatusFileLoggerTest, argc, argv);
    QTest::qExec(new ConfigTest, argc, argv);

    return 0;
}

#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "statusprinttest.h"
#include "statusfileloggertest.h"
#include "configtest.h"
#include "strtest.h"
#include "filetest.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTest::qExec(new StatusPrintTest, argc, argv);
    QTest::qExec(new StatusFileLoggerTest, argc, argv);
    QTest::qExec(new ConfigTest, argc, argv);
    QTest::qExec(new StrTest, argc, argv);
    QTest::qExec(new FileTest, argc, argv);

    Q_UNUSED(a)

    return 0;
}

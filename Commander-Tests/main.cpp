#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "status_print_test.h"
#include "status_file_logger_test.h"
#include "config_test.h"
#include "str_test.h"
#include "file_test.h"

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

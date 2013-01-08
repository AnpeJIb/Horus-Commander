#include <QCoreApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include "server_emulator_test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTest::qExec(new ServerEmulatorTest, argc, argv);

    Q_UNUSED(a)
    return 0;
}


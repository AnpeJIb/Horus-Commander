#include <QCoreApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include "single_connectioned_echo_stream_server_test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    int result = 0;

    result += QTest::qExec(new SingleConnectionedEchoStreamServerTest, argc, argv);

    return result;
}

#include <QCoreApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include "single_connectioned_echo_stream_server_test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QTest::qExec(new SingleConnectionedEchoStreamServerTest, argc, argv);

    Q_UNUSED(a)
    return 0;
}

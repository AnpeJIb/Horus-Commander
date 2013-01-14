#include <QCoreApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include "file_line_reader_test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    int result = 0;

    result += QTest::qExec(new FileLineReaderTest, argc, argv);

    return result;
}

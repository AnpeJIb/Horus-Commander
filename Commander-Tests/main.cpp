#include <QApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include "status_print_test.h"
#include "status_file_logger_test.h"
#include "str_test.h"
#include "file_test.h"
#include "model_xml_dao_test.h"
#include "model_parameter_xml_dao_test.h"
#include "general_config_test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTest::qExec(new StatusPrintTest, argc, argv);
    QTest::qExec(new StatusFileLoggerTest, argc, argv);
    QTest::qExec(new StrTest, argc, argv);
    QTest::qExec(new FileTest, argc, argv);
    QTest::qExec(new ModelXmlDaoTest, argc, argv);
    QTest::qExec(new ModelParameterXmlDaoTest, argc, argv);
    //QTest::qExec(new GeneralConfigTest, argc, argv);

    Q_UNUSED(a)

    return 0;
}

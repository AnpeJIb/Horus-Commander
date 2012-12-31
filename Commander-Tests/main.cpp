#include <QApplication>
#include <QTest>
#include <cstdlib>
#include <cstdio>

#include "log_service_test.h"
#include "file_logger_test.h"
#include "str_test.h"
#include "file_test.h"

#include "model_xml_dao_test.h"
#include "simple_parameter_xml_dao_test.h"
#include "model_parameter_xml_dao_test.h"
#include "scheme_xml_dao_test.h"
#include "model_parameter_value_xml_dao_test.h"

#include "system_path_test.h"
#include "primary_config_service_test.h"
#include "general_config_service_test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTest::qExec(new LogServiceTest, argc, argv);
    QTest::qExec(new FileLoggerTest, argc, argv);
    QTest::qExec(new StrTest, argc, argv);
    QTest::qExec(new FileTest, argc, argv);

    QTest::qExec(new ModelXmlDaoTest, argc, argv);
    QTest::qExec(new SimpleParameterXmlDaoTest, argc, argv);
    QTest::qExec(new ModelParameterXmlDaoTest, argc, argv);
    QTest::qExec(new SchemeXmlDaoTest, argc, argv);
    QTest::qExec(new ModelParameterValueXmlDaoTest, argc, argv);

    QTest::qExec(new SystemPathTest, argc, argv);
    QTest::qExec(new PrimaryConfigServiceTest, argc, argv);
    QTest::qExec(new GeneralConfigServiceTest, argc, argv);

    Q_UNUSED(a)

    return 0;
}

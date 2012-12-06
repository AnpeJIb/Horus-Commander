#ifndef CONFIGTEST_H
#define CONFIGTEST_H

#include <QObject>
#include "foo_status_printer.h"
#include "common_log_config.h"

class ConfigTest: public QObject
{
    Q_OBJECT
public:
    explicit ConfigTest(QObject *parent = 0);

private slots:
    void initTestCase();

    void test_general_lang();
    void test_general_daemonMode();
    void test_general_serverPath();
    void test_general_serverName();
    void test_general_serverDescr();

    void test_log_file();
    void test_log_gui();

    void test_window_geometry();
    void test_window_minimized();
    void test_window_quitOnClose();
    void test_window_promptClose();

    void cleanupTestCase();

private:
    void test_log(CommonLogConfig* cfg);
    void test_log_enable(CommonLogConfig* cfg);
    void test_log_level(CommonLogConfig* cfg);

    FooStatusPrinter printer;
};

#endif // CONFIGTEST_H

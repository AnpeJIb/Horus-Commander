#ifndef CONFIGTEST_H
#define CONFIGTEST_H

#include <QObject>
#include "foostatusprinter.h"
#include "commonlogconfig.h"

class ConfigTest: public QObject
{
    Q_OBJECT
public:
    explicit ConfigTest(QObject *parent = 0);

private slots:
    void initTestCase();

    void test_general_lang();
    void test_general_daemonMode();

    void test_log_file();
    void test_log_gui();

    void cleanupTestCase();

private:
    void test_log(CommonLogConfig* cfg);
    void test_log_enable(CommonLogConfig* cfg);
    void test_log_level(CommonLogConfig* cfg);

    FooStatusPrinter printer;
};

#endif // CONFIGTEST_H

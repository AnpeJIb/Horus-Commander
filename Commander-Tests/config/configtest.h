#ifndef CONFIGTEST_H
#define CONFIGTEST_H

#include <QObject>
#include "foostatusprinter.h"

class ConfigTest: public QObject
{
    Q_OBJECT
public:
    explicit ConfigTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void test_general_lang();
    void test_general_daemonMode();
    void cleanupTestCase();

private:

    FooStatusPrinter printer;
};

#endif // CONFIGTEST_H

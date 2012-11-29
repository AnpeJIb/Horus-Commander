#include "configtest.h"
#include "config.h"

#include <QtTest/QtTest>
#include <QFile>

ConfigTest::ConfigTest(QObject *parent)
    : QObject(parent)
{
}

void ConfigTest::initTestCase()
{
    printer.setLevel(StatusPrinter::ALL);
    STATUS_PRINT::REGISTER(&printer);

    QFile::remove(CONFIG::PATH());

    /** init CONFIG */
    static CONFIG cfg;
    Q_UNUSED(cfg);
}

void ConfigTest::test_general_lang()
{
    QVERIFY(CONFIG::IS_CHANGED()==false);
    CONFIG::DEFAULTS();
    QVERIFY(CONFIG::IS_CHANGED()==true);
    QVERIFY(CONFIG::GENERAL.langCode()=="en");

    CONFIG::GENERAL.setLangCode("ru");
    CONFIG::SAVE();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    CONFIG::DEFAULTS();
    QVERIFY(CONFIG::GENERAL.langCode()=="en");

    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::LOAD();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    QVERIFY(CONFIG::GENERAL.langCode()=="ru");
}

void ConfigTest::test_general_daemonMode()
{
    QVERIFY(CONFIG::IS_CHANGED()==false);
    CONFIG::DEFAULTS();
    QVERIFY(CONFIG::IS_CHANGED()==true);
    QVERIFY(CONFIG::GENERAL.isDaemonMode()==false);

    CONFIG::GENERAL.setDaemonMode(true);
    CONFIG::SAVE();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    CONFIG::DEFAULTS();
    QVERIFY(CONFIG::GENERAL.isDaemonMode()==false);

    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::LOAD();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    QVERIFY(CONFIG::GENERAL.isDaemonMode()==true);
}

void ConfigTest::cleanupTestCase()
{
    STATUS_PRINT::UNREGISTER(&printer);
    QFile::remove(CONFIG::PATH());
}

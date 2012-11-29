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

void ConfigTest::testGeneralConfig()
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

void ConfigTest::cleanupTestCase()
{
    STATUS_PRINT::UNREGISTER(&printer);
    QFile::remove(CONFIG::PATH());
}

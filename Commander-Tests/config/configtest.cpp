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
    QVERIFY(CONFIG::IS_CHANGED()==true);
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
    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::SAVE();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    CONFIG::DEFAULTS();
    QVERIFY(CONFIG::GENERAL.isDaemonMode()==false);

    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::LOAD();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    QVERIFY(CONFIG::GENERAL.isDaemonMode()==true);
}

void ConfigTest::test_log_file(){test_log(CONFIG::LOG.FILE());}
void ConfigTest::test_log_gui() {test_log(CONFIG::LOG.GUI());}

void ConfigTest::test_log(CommonLogConfig *cfg)
{
    test_log_enable(cfg);
    test_log_level(cfg);
}

void ConfigTest::test_log_enable(CommonLogConfig *cfg)
{
    CONFIG::DEFAULTS();
    QVERIFY(cfg->isEnable()==true);

    cfg->setEnable(false);
    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::SAVE();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    CONFIG::DEFAULTS();
    QVERIFY(cfg->isEnable()==true);

    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::LOAD();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    QVERIFY(cfg->isEnable()==false);
}

void ConfigTest::test_log_level(CommonLogConfig *cfg)
{
    CONFIG::DEFAULTS();
    QVERIFY(cfg->level()==StatusPrinter::ALL);

    cfg->setLevel(StatusPrinter::INFO);
    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::SAVE();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    CONFIG::DEFAULTS();
    QVERIFY(cfg->level()==StatusPrinter::ALL);

    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::LOAD();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    QVERIFY(cfg->level()==StatusPrinter::INFO);
}

void ConfigTest::test_window_geometry()
{
    QRect geometry;

    CONFIG::DEFAULTS();
    geometry = CONFIG::WINDOW.geometry();
    QVERIFY(geometry.x()==0);
    QVERIFY(geometry.y()==0);
    QVERIFY(geometry.height()==200);
    QVERIFY(geometry.width()==300);

    geometry.setRect(20, 25, 400, 250);
    CONFIG::WINDOW.setGeometry(geometry);
    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::SAVE();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    CONFIG::DEFAULTS();

    geometry = CONFIG::WINDOW.geometry();    
    QVERIFY(geometry.x()==0);
    QVERIFY(geometry.y()==0);
    QVERIFY(geometry.height()==200);
    QVERIFY(geometry.width()==300);


    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::LOAD();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    geometry = CONFIG::WINDOW.geometry();
    QVERIFY(geometry.x()==20);
    QVERIFY(geometry.y()==25);
    QVERIFY(geometry.height()==250);
    QVERIFY(geometry.width()==400);
}

void ConfigTest::test_window_minimized()
{
    CONFIG::DEFAULTS();
    QVERIFY(CONFIG::WINDOW.isMinimized()==false);

    CONFIG::WINDOW.setMinimized(true);
    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::SAVE();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    CONFIG::DEFAULTS();
    QVERIFY(CONFIG::WINDOW.isMinimized()==false);

    QVERIFY(CONFIG::IS_CHANGED()==true);
    CONFIG::LOAD();
    QVERIFY(CONFIG::IS_CHANGED()==false);
    QVERIFY(CONFIG::WINDOW.isMinimized()==true);
}

void ConfigTest::cleanupTestCase()
{
    STATUS_PRINT::UNREGISTER(&printer);
    QFile::remove(CONFIG::PATH());
}

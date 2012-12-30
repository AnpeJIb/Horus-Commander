#include "general_config_service_test.h"

#include <QFile>
#include <QList>
#include <QtTest/QtTest>

#include "primary_config_service.h"

GeneralConfigServiceTest::GeneralConfigServiceTest(QObject *parent)
    : QObject(parent)
{
    configPath = "generalConfigTest.ini";
    dsPath = "generalConfigTestDataSource.xml";
}

void GeneralConfigServiceTest::initTestCase()
{
    QVERIFY(QFile::exists(configPath) == false);
    QVERIFY(QFile::exists(dsPath)     == false);

    Service::ConfigService::PrimaryConfigService::init(configPath, dsPath);
}

void GeneralConfigServiceTest::testLanguageCode()
{
    QCOMPARE(service.languageCode(), QString("en"));

    service.setLanguageCode("ru");
    QCOMPARE(service.languageCode(), QString("ru"));
}

void GeneralConfigServiceTest::cleanupTestCase()
{
    Service::ConfigService::PrimaryConfigService::cleanUp();

    QFile::remove(configPath);
    QFile::remove(dsPath);

    QVERIFY(QFile::exists(configPath) == false);
    QVERIFY(QFile::exists(dsPath)     == false);
}

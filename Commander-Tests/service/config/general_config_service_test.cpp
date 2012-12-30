#include "general_config_service_test.h"

#include <QFile>
#include <QDir>
#include <QtTest/QtTest>

#include "primary_config_service.h"
#include "general_config.h"

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
    QList<Config::General::SupportedLanguage> langs = Config::General::supportedLanguages();
    QCOMPARE(langs.count(), 2);
    QCOMPARE(langs.at(0).codeName, QString("en"));
    QCOMPARE(langs.at(1).codeName, QString("ru"));

    QCOMPARE(service.languageCode(), langs.at(0).codeName);

    service.setLanguageCode(langs.at(1).codeName);
    QCOMPARE(service.languageCode(), langs.at(1).codeName);
}

void GeneralConfigServiceTest::testServerPath()
{
    QCOMPARE(service.serverPath(), QDir::currentPath());

    service.setServerPath("/some/path/to/server");
    QCOMPARE(service.serverPath(), QString("/some/path/to/server"));
}

void GeneralConfigServiceTest::testDBstrings()
{
    QList<Config::General::SupportedDB> DBs = Config::General::supportedDatabases();
    QCOMPARE(DBs.count(), 1);

    QCOMPARE(DBs.at(0).title, QString("SQLite"));
    QVERIFY (DBs.at(0).kind == Config::General::DB_SQLITE);

    QCOMPARE(service.dbKind(), Config::General::DB_SQLITE);
}

void GeneralConfigServiceTest::cleanupTestCase()
{
    Service::ConfigService::PrimaryConfigService::cleanUp();

    QFile::remove(configPath);
    QFile::remove(dsPath);

    QVERIFY(QFile::exists(configPath) == false);
    QVERIFY(QFile::exists(dsPath)     == false);
}

#include "primary_config_service_test.h"

#include <QFile>
#include <QList>
#include <QtTest/QtTest>

#include "primary_config_service.h"
#include "xml_dao_helper.h"
#include "scheme_xml_dao.h"

PrimaryConfigServiceTest::PrimaryConfigServiceTest(QObject *parent)
    : QObject(parent)
{
    configPath = "config.ini";
    dsPath = "dataSource.xml";
}

void PrimaryConfigServiceTest::initTestCase()
{
    QVERIFY(QFile::exists(configPath) == false);
    QVERIFY(QFile::exists(dsPath)     == false);

    Service::ConfigService::PrimaryConfigService::init(configPath, dsPath);
}

void PrimaryConfigServiceTest::testCurrentScheme()
{
    Scheme* sch = Service::ConfigService::PrimaryConfigService::currentScheme();
    QVERIFY(sch != NULL);
    QVERIFY(sch->id == Q_UINT64_C(1));
    QVERIFY(sch->title == "Default");
    QVERIFY(sch->description == "Default primary config scheme");
}

void PrimaryConfigServiceTest::testGetAllSchemes()
{
    QList<Scheme*> lst;
    Service::ConfigService::PrimaryConfigService::schemes(&lst);
    QVERIFY(lst.count() == 1);
}

void PrimaryConfigServiceTest::testCopyCurrentSchemeAndSelect()
{
    Service::ConfigService::PrimaryConfigService::copyCurrentSchemeAndSelect();

    QList<Scheme*> lst;
    Service::ConfigService::PrimaryConfigService::schemes(&lst);
    QVERIFY(lst.count() == 2);

    Scheme* original = lst.at(0);
    Scheme* copied = lst.at(1);

    QVERIFY(copied->id != original->id);
    QVERIFY(copied == Service::ConfigService::PrimaryConfigService::currentScheme());
    QVERIFY(copied->title == "Default (copy)");
    QVERIFY(copied->description == "Copy of Default primary config scheme");
    QVERIFY(copied->model() == original->model());
}

void PrimaryConfigServiceTest::testSelectCurrentScheme()
{
    Service::ConfigService::PrimaryConfigService::selectCurrentScheme(Q_UINT64_C(1));

    Scheme* sch = Service::ConfigService::PrimaryConfigService::currentScheme();
    QVERIFY(sch != NULL);
    QVERIFY(sch->id == Q_UINT64_C(1));
    QVERIFY(sch->title == "Default");
    QVERIFY(sch->description == "Default primary config scheme");
}

void PrimaryConfigServiceTest::testRemoveCurrentScheme()
{
    Service::ConfigService::PrimaryConfigService::removeCurrentScheme();

    QList<Scheme*> lst;
    Service::ConfigService::PrimaryConfigService::schemes(&lst);
    QVERIFY(lst.count() == 1);

    Scheme* sch = Service::ConfigService::PrimaryConfigService::currentScheme();
    QVERIFY(sch->id == Q_UINT64_C(2));
    QVERIFY(sch->title == "Default (copy)");
}

void PrimaryConfigServiceTest::testUpdateCurrentScheme()
{
    Scheme* sch = Service::ConfigService::PrimaryConfigService::currentScheme();
    QVERIFY(sch != NULL);

    sch->title = "Modified";
    sch->description = "Modified copy of default primary config scheme";

    Service::ConfigService::PrimaryConfigService::updateCurrentScheme();

    Service::ConfigService::PrimaryConfigService::cleanUp();
    Service::ConfigService::PrimaryConfigService::init(configPath, dsPath);

    sch = Service::ConfigService::PrimaryConfigService::currentScheme();
    QVERIFY(sch != NULL);
    QVERIFY(sch->id == Q_UINT64_C(2));
    QVERIFY(sch->title == "Modified");
    QVERIFY(sch->description == "Modified copy of default primary config scheme");

    Model* m = sch->model();
    QVERIFY(m != NULL);
    QVERIFY(m->kind  == Model::SETTINGS_PRIMARY);
    QVERIFY(m->title == "Primary config model");
}

void PrimaryConfigServiceTest::cleanupTestCase()
{
    Service::ConfigService::PrimaryConfigService::cleanUp();

    QVERIFY(QFile::exists(configPath));
    QVERIFY(QFile::exists(dsPath));

    Dao::XmlDaoHelper::tearDown();
    Dao::XmlDaoBase::clearUp();

    QFile::remove(configPath);

    QVERIFY(QFile::exists(configPath) == false);
    QVERIFY(QFile::exists(dsPath)     == false);
}

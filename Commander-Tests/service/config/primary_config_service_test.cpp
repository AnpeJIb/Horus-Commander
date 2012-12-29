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

    Config::PrimaryConfigService::init(configPath, dsPath);
}

void PrimaryConfigServiceTest::testGetAllSchemes()
{
    QList<Scheme*> lst;
    Config::PrimaryConfigService::shemes(&lst);
    QVERIFY(lst.count() == 1);
}

void PrimaryConfigServiceTest::cleanupConfig()
{
    Config::PrimaryConfigService::cleanUp();

    QVERIFY(QFile::exists(configPath));
    QVERIFY(QFile::exists(dsPath));
}

void PrimaryConfigServiceTest::testSchemeFind()
{
    Dao::XmlDaoBase::init(dsPath);

    domain_id_t id = Q_UINT64_C(1);

    Dao::Parameters::SchemeXmlDao schemeDao;
    Scheme* sch = schemeDao.find(id);

    QVERIFY(sch != NULL);
    QVERIFY(sch->id    == id);
    QVERIFY(sch->title == "Default");
    QVERIFY(sch->description == "Default primary config scheme");

    Model* m = sch->model();
    QVERIFY(m != NULL);
    QVERIFY(m->kind  == Model::MODEL_PRIMARY_SETTINGS);
    QVERIFY(m->title == "Primary config model");
}

void PrimaryConfigServiceTest::cleanupTestCase()
{
    Dao::XmlDaoHelper::tearDown();
    Dao::XmlDaoBase::clearUp();

    QFile::remove(configPath);

    QVERIFY(QFile::exists(configPath) == false);
    QVERIFY(QFile::exists(dsPath)     == false);
}

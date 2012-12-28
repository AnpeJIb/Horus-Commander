#include "primary_config_helper_test.h"

#include <QFile>
#include <QtTest/QtTest>

#include "primary_config_helper.h"
#include "xml_dao_helper.h"
#include "scheme_xml_dao.h"

PrimaryConfigHelperTest::PrimaryConfigHelperTest(QObject *parent)
    : QObject(parent)
{
    configPath = "config.ini";
    dsPath = "dataSource.xml";
}

void PrimaryConfigHelperTest::initTestCase()
{
    QVERIFY(QFile::exists(configPath) == false);
    QVERIFY(QFile::exists(dsPath)     == false);

    Config::PrimaryConfigHelper::init(configPath, dsPath);
    Config::PrimaryConfigHelper::cleanUp();

    QVERIFY(QFile::exists(configPath));
    QVERIFY(QFile::exists(dsPath));
}

void PrimaryConfigHelperTest::testScheme()
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

void PrimaryConfigHelperTest::cleanupTestCase()
{
    Dao::XmlDaoHelper::tearDown();
    Dao::XmlDaoBase::clearUp();

    QFile::remove(configPath);

    QVERIFY(QFile::exists(configPath) == false);
    QVERIFY(QFile::exists(dsPath)     == false);
}

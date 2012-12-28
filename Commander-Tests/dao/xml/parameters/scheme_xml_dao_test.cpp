#include "scheme_xml_dao_test.h"

#include <QFile>
#include <QtTest/QtTest>

SchemeXmlDaoTest::SchemeXmlDaoTest(QObject *parent)
    : QObject(parent)
{
    m_path = "schemeDaoTest.xml";
}

void SchemeXmlDaoTest::initTestCase()
{
    XmlDaoBase::init(m_path);
    QVERIFY(QFile::exists(m_path));

    modelDao = new ModelXmlDao;
    schemeDao = new SchemeXmlDao;
}

void SchemeXmlDaoTest::testFindNone()
{
    Scheme* sch = schemeDao->find(Q_UINT64_C(1));
    QVERIFY(sch == NULL);
}

void SchemeXmlDaoTest::testSave()
{
    domain_id_t nullId = Q_UINT64_C(0);

    /** Save models */

    Model* m1 = new Model;
    m1->kind  = Model::MODEL_PRIMARY_SETTINGS;
    m1->title = "Foo settings model";
    modelDao->save(m1);
    QVERIFY(m1->id > nullId);

    Model* m2 = new Model;
    m2->kind  = Model::MODEL_AWARD_ASSIGN;
    m2->title = "Foo assignment model";
    modelDao->save(m2);

    QVERIFY(m2->id > nullId);
    QVERIFY(m2->id != m1->id);

    /** Save schemes */

    Scheme* sch1 = new Scheme(schemeDao);
    sch1->title = "Default";
    sch1->description = "Default settings scheme";
    sch1->setModel(m1);
    schemeDao->save(sch1);
    QVERIFY(sch1->id > nullId);

    Scheme* sch2 = new Scheme(schemeDao);
    sch2->title = "Custom";
    sch2->description = "Some custom settings";
    sch2->setModel(m1);
    schemeDao->save(sch2);
    QVERIFY(sch2->id > nullId);

    Scheme* sch3 = new Scheme(schemeDao);
    sch3->title = "Default";
    sch3->description = "Default assignment scheme";
    sch3->setModel(m2);
    schemeDao->save(sch3);
    QVERIFY(sch3->id > nullId);

    Scheme* sch4 = new Scheme(schemeDao);
    sch4->title = "Custom";
    sch4->description = "Some custom assignment";
    sch4->setModel(m2);
    schemeDao->save(sch4);
    QVERIFY(sch4->id > nullId);

    XmlDaoBase::sync();

    delete sch1;
    delete sch2;
    delete sch3;
    delete sch4;

    delete m1;
    delete m2;

    ModelXmlDao::clearCache();
    SchemeDao::clearCache();
}

void SchemeXmlDaoTest::testAll()
{
    QList< Scheme* > lst;
    schemeDao->all(&lst);
    QVERIFY(lst.count() == 4);
}

void SchemeXmlDaoTest::testFindById()
{
    /** Test Scheme 1 */

    Scheme* sch1 = schemeDao->find(Q_UINT64_C(1));

    QVERIFY(sch1 != NULL);
    QVERIFY(sch1->id    == Q_UINT64_C(1));
    QVERIFY(sch1->title == "Default");
    QVERIFY(sch1->description  == "Default settings scheme");

    Model* m1 = sch1->model();

    QVERIFY(m1 != NULL);
    QVERIFY(m1->id    == Q_UINT64_C(1));
    QVERIFY(m1->kind  == Model::MODEL_PRIMARY_SETTINGS);
    QVERIFY(m1->title == "Foo settings model");

    /** Test Scheme 2 */

    Scheme* sch2 = schemeDao->find(Q_UINT64_C(2));

    QVERIFY(sch2 != NULL);
    QVERIFY(sch2->id    == Q_UINT64_C(2));
    QVERIFY(sch2->title == "Custom");
    QVERIFY(sch2->description  == "Some custom settings");

    Model* m2 = sch2->model();

    QVERIFY(m2 != NULL);
    QVERIFY(m2 == m1);

    /** Test Scheme 3 */

    Scheme* sch3 = schemeDao->find(Q_UINT64_C(3));

    QVERIFY(sch3 != NULL);
    QVERIFY(sch3->id    == Q_UINT64_C(3));
    QVERIFY(sch3->title == "Default");
    QVERIFY(sch3->description  == "Default assignment scheme");

    Model* m3 = sch3->model();

    QVERIFY(m3 != NULL);
    QVERIFY(m3->id    == Q_UINT64_C(2));
    QVERIFY(m3->kind  == Model::MODEL_AWARD_ASSIGN);
    QVERIFY(m3->title == "Foo assignment model");

    /** Test Scheme 4 */

    Scheme* sch4 = schemeDao->find(Q_UINT64_C(4));

    QVERIFY(sch4 != NULL);
    QVERIFY(sch4->id    == Q_UINT64_C(4));
    QVERIFY(sch4->title == "Custom");
    QVERIFY(sch4->description  == "Some custom assignment");

    Model* m4 = sch4->model();

    QVERIFY(m4 != NULL);
    QVERIFY(m4 == m3);
}

void SchemeXmlDaoTest::testReferentialIntegrity()
{
    domain_id_t id = Q_UINT64_C(1);

    Scheme* sch1 = schemeDao->find(id);
    Scheme* sch2 = schemeDao->find(id);

    QVERIFY(sch1 == sch2);
}

void SchemeXmlDaoTest::testFindByTitle()
{
    domain_id_t id = Q_UINT64_C(1);
    QList< Scheme* > lst;

    schemeDao->findByTitle("Default", &lst);
    QVERIFY(lst.count() == 2);

    Scheme* sch1 = lst.at(0);

    QVERIFY(sch1->id    == id);
    QVERIFY(sch1->title == "Default");
    QVERIFY(sch1->description  == "Default settings scheme");

    Scheme* sch2 = schemeDao->find(id);
    QVERIFY(sch1 == sch2);
}

void SchemeXmlDaoTest::testFindByDescription()
{
    domain_id_t id = Q_UINT64_C(3);
    QList< Scheme* > lst;

    schemeDao->findByDescription("Default assignment scheme", &lst);
    QVERIFY(lst.count() == 1);

    Scheme* sch1 = lst.at(0);

    QVERIFY(sch1->id    == id);
    QVERIFY(sch1->title == "Default");
    QVERIFY(sch1->description  == "Default assignment scheme");

    Scheme* sch2 = schemeDao->find(id);
    QVERIFY(sch1 == sch2);
}

void SchemeXmlDaoTest::testFindByModel()
{
    Model* m = modelDao->find(Q_UINT64_C(1));
    QVERIFY(m != NULL);

    QList< Scheme* > lst;
    schemeDao->findByModel(m, &lst);
    QVERIFY(lst.count() == 2);

    Scheme* mp1 = lst.at(0);
    Scheme* mp2 = schemeDao->find(Q_UINT64_C(1));

    QVERIFY(mp2 != NULL);
    QVERIFY(mp1 == mp2);
}

void SchemeXmlDaoTest::testUpdate()
{
    domain_id_t id = Q_UINT64_C(1);

    Scheme* sch1 = schemeDao->find(id);
    QVERIFY(sch1 != NULL);

    Model* m1 = modelDao->find(Q_UINT64_C(2));
    QVERIFY(m1 != NULL);

    sch1->title = "Not default";
    sch1->setModel(m1);
    schemeDao->update(sch1);

    XmlDaoBase::sync();
    SchemeXmlDao::clearCache();
    QList<Scheme* > lst;
    schemeDao->all(&lst);

    Scheme* sch2 = schemeDao->find(id);

    QVERIFY(sch2 != NULL);
    QVERIFY(sch2->title != "Default");

    QVERIFY(sch1->id    == sch2->id);
    QVERIFY(sch1->title == sch2->title);
    QVERIFY(sch1->description == sch2->description);
    QVERIFY(sch1->model()     == sch2->model());
}

void SchemeXmlDaoTest::testRemove()
{
    domain_id_t id = Q_UINT64_C(2);

    Scheme* sch1 = schemeDao->find(id);
    QVERIFY(sch1 != NULL);

    schemeDao->remove(sch1);
    XmlDaoBase::sync();

    Scheme* sch2 = schemeDao->find(id);
    QVERIFY(sch2 == NULL);
}

void SchemeXmlDaoTest::cleanupTestCase()
{
    SchemeXmlDao::clearCacheAndDisposeDomains();
    ModelXmlDao::clearCacheAndDisposeDomains();

    SchemeXmlDao::resetCurrentId();
    ModelXmlDao::resetCurrentId();

    delete (SchemeXmlDao*) schemeDao;
    delete (ModelXmlDao*) modelDao;

    XmlDaoBase::clearUp();
    QVERIFY(QFile::exists(m_path)==false);
}

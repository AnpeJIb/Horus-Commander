#include "simple_parameter_xml_dao_test.h"

#include <QFile>
#include <QtTest/QtTest>

SimpleParameterXmlDaoTest::SimpleParameterXmlDaoTest(QObject *parent)
    : QObject(parent)
{
    m_path = "simpleParameterDaoTest.xml";
}

void SimpleParameterXmlDaoTest::initTestCase()
{
    XmlDaoBase::init(m_path);
    QVERIFY(QFile::exists(m_path));

    dao = new SimpleParameterXmlDao;
}

void SimpleParameterXmlDaoTest::testFindNone()
{
    SimpleParameter* m = dao->find(Q_UINT64_C(1));
    QVERIFY(m == NULL);
}

void SimpleParameterXmlDaoTest::testSave()
{
    domain_id_t nullId = Q_UINT64_C(0);

    SimpleParameter* p1 = new SimpleParameter;
    p1->title = "Kill air enemies";
    p1->codeName = "KILL_EAIR";
    dao->save(p1);
    QVERIFY(p1->id > nullId);

    SimpleParameter* p2 = new SimpleParameter;
    p2->title = "Fly time";
    p2->codeName = "FLY_TIME";
    dao->save(p2);

    QVERIFY(p2->id > nullId);
    QVERIFY(p2->id != p1->id);

    XmlDaoBase::sync();
}

void SimpleParameterXmlDaoTest::testAll()
{
    QList< SimpleParameter* > lst;
    dao->all(&lst);
    QVERIFY(lst.count() == 2);
}

void SimpleParameterXmlDaoTest::testFindById()
{
    SimpleParameter* p = dao->find(Q_UINT64_C(1));

    QVERIFY(p != NULL);
    QVERIFY(p->id    == Q_UINT64_C(1));
    QVERIFY(p->title == "Kill air enemies");
    QVERIFY(p->codeName == "KILL_EAIR");
}

void SimpleParameterXmlDaoTest::testReferentialIntegrity()
{
    domain_id_t id = Q_UINT64_C(1);

    SimpleParameter* p1 = dao->find(id);
    SimpleParameter* p2 = dao->find(id);

    QVERIFY(p1 == p2);
}

void SimpleParameterXmlDaoTest::testFindByCodeName()
{
    domain_id_t id = Q_UINT64_C(1);
    QList< SimpleParameter* > lst;

    dao->findByCodeName("KILL_EAIR", &lst);
    QVERIFY(lst.count() == 1);

    SimpleParameter* p1 = lst.at(0);

    QVERIFY(p1->id       == id);
    QVERIFY(p1->title    == "Kill air enemies");
    QVERIFY(p1->codeName == "KILL_EAIR");

    SimpleParameter* p2 = dao->find(id);
    QVERIFY(p1 == p2);
}

void SimpleParameterXmlDaoTest::testFindByTitle()
{
    domain_id_t id = Q_UINT64_C(2);
    QList< SimpleParameter* > lst;

    dao->findByTitle("Fly time", &lst);
    QVERIFY(lst.count() == 1);

    SimpleParameter* p1 = lst.at(0);

    QVERIFY(p1->id       == id);
    QVERIFY(p1->title    == "Fly time");
    QVERIFY(p1->codeName == "FLY_TIME");

    SimpleParameter* p2 = dao->find(id);
    QVERIFY(p1 == p2);
}

void SimpleParameterXmlDaoTest::testUpdate()
{
    domain_id_t id = Q_UINT64_C(1);

    SimpleParameter* p1 = dao->find(id);
    QVERIFY(p1 != NULL);

    p1->title = "Modified fly time";
    dao->update(p1);

    XmlDaoBase::sync();
    SimpleParameterXmlDao::clearCache();
    QList< SimpleParameter* > lst;
    dao->all(&lst);

    SimpleParameter* p2 = dao->find(id);

    QVERIFY(p2 != NULL);

    QVERIFY(p1->id       == p2->id);
    QVERIFY(p1->title    != "Fly time");
    QVERIFY(p1->title    == p2->title);
    QVERIFY(p1->codeName == p2->codeName);
}

void SimpleParameterXmlDaoTest::testRemove()
{
    domain_id_t id = Q_UINT64_C(2);

    SimpleParameter* p1 = dao->find(id);
    QVERIFY(p1 != NULL);

    dao->remove(p1);
    XmlDaoBase::sync();

    SimpleParameter* p2 = dao->find(id);
    QVERIFY(p2 == NULL);
}

void SimpleParameterXmlDaoTest::cleanupTestCase()
{
    SimpleParameterXmlDao::clearCacheAndDisposeDomains();
    SimpleParameterXmlDao::resetCurrentId();

    delete (SimpleParameterXmlDao*) dao;

    XmlDaoBase::clearUp();
    QVERIFY(QFile::exists(m_path)==false);
}

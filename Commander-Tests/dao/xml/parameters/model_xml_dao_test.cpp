#include "model_xml_dao_test.h"

#include <QFile>
#include <QtTest/QtTest>

using namespace Domain::Parameters;

ModelXmlDaoTest::ModelXmlDaoTest(QObject *parent)
    : QObject(parent)
{
    m_path = "modelDaoTest.xml";
}

void ModelXmlDaoTest::initTestCase()
{
    XmlDaoBase::init(m_path);
    QVERIFY(QFile::exists(m_path));

    dao = new ModelXmlDao;
}

void ModelXmlDaoTest::testFindNone()
{
    Model* m = dao->find(Q_UINT64_C(1));
    QVERIFY(m == NULL);
}

void ModelXmlDaoTest::testSave()
{
    domain_id_t nullId = Q_UINT64_C(0);

    Model* m1 = new Model;
    m1->kind  = Model::MODEL_PRIMARY_SETTINGS;
    m1->title = "Foo settings model";
    dao->save(m1);
    QVERIFY(m1->id > nullId);

    Model* m2 = new Model;
    m2->kind  = Model::MODEL_AWARD_ASSIGN;
    m2->title = "Foo assignment model";
    dao->save(m2);

    QVERIFY(m2->id > nullId);
    QVERIFY(m2->id != m1->id);

    XmlDaoBase::sync();
}

void ModelXmlDaoTest::testAll()
{
    QList< Model* > lst;
    dao->all(&lst);
    QVERIFY(lst.count() == 2);
}

void ModelXmlDaoTest::testFindById()
{
    Model* m = dao->find(Q_UINT64_C(1));

    QVERIFY(m != NULL);
    QVERIFY(m->id    == Q_UINT64_C(1));
    QVERIFY(m->kind  == Model::MODEL_PRIMARY_SETTINGS);
    QVERIFY(m->title == "Foo settings model");
}

void ModelXmlDaoTest::testReferentialIntegrity()
{
    domain_id_t id = Q_UINT64_C(1);

    Model* m1 = dao->find(id);
    Model* m2 = dao->find(id);

    QVERIFY(m1 == m2);
}

void ModelXmlDaoTest::testFindByKind()
{
    domain_id_t id = Q_UINT64_C(1);
    QList< Model* > lst;

    dao->findByKind(Model::MODEL_PRIMARY_SETTINGS, &lst);
    QVERIFY(lst.count() == 1);

    Model* m1 = lst.at(0);

    QVERIFY(m1->id    == id);
    QVERIFY(m1->kind  == Model::MODEL_PRIMARY_SETTINGS);
    QVERIFY(m1->title == "Foo settings model");

    Model* m2 = dao->find(id);
    QVERIFY(m1 == m2);
}

void ModelXmlDaoTest::testFindByTitle()
{
    domain_id_t id = Q_UINT64_C(2);
    QList< Model* > lst;

    dao->findByTitle("Foo assignment model", &lst);
    QVERIFY(lst.count() == 1);

    Model* m1 = lst.at(0);

    QVERIFY(m1->id    == id);
    QVERIFY(m1->kind  == Model::MODEL_AWARD_ASSIGN);
    QVERIFY(m1->title == "Foo assignment model");

    Model* m2 = dao->find(id);
    QVERIFY(m1 == m2);
}

void ModelXmlDaoTest::testUpdate()
{
    domain_id_t id = Q_UINT64_C(1);

    Model* m1 = dao->find(id);
    QVERIFY(m1 != NULL);

    m1->title = "Modified foo settings model";
    dao->update(m1);

    XmlDaoBase::sync();
    ModelXmlDao::clearCache();
    QList< Model* > lst;
    dao->all(&lst);

    Model* m2 = dao->find(id);

    QVERIFY(m2 != NULL);
    QVERIFY(m2->title != "Foo settings model");
    QVERIFY(m1->id    == m2->id);
    QVERIFY(m1->kind  == m2->kind);
    QVERIFY(m1->title == m2->title);
}

void ModelXmlDaoTest::testRemove()
{
    domain_id_t id = Q_UINT64_C(2);

    Model* m1 = dao->find(id);
    QVERIFY(m1 != NULL);

    dao->remove(m1);
    XmlDaoBase::sync();

    Model* m2 = dao->find(id);
    QVERIFY(m2 == NULL);
}

void ModelXmlDaoTest::cleanupTestCase()
{
    ModelXmlDao::clearCacheAndDisposeDomains();
    ModelXmlDao::resetCurrentId();

    delete (ModelXmlDao*) dao;

    XmlDaoBase::clearUp();
    QVERIFY(QFile::exists(m_path)==false);
}

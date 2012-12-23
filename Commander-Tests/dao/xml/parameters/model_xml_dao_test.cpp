#include "model_xml_dao_test.h"

#include <QFile>
#include <QtTest/QtTest>

using namespace Domain::Parameters;

ModelXmlDaoTest::ModelXmlDaoTest(QObject *parent)
    : QObject(parent)
{
    m_path = "modelTest.xml";
}

void ModelXmlDaoTest::initTestCase()
{
    XmlDao::init(m_path);
    QVERIFY(QFile::exists(m_path));
}

void ModelXmlDaoTest::testFindNone()
{
    Model m;
    QVERIFY(m_dao.find(Q_UINT64_C(1), &m) == false);
}

void ModelXmlDaoTest::testSave()
{
    Model m1;
    m1.kind = Model::MODEL_SETTINGS;
    m1.title = "Foo settings model";
    m_dao.save(&m1);
    QVERIFY(m1.id > 0);

    Model m2;
    m2.kind = Model::MODEL_AWARD_ASSIGN;
    m2.title = "Foo assignment model";
    m_dao.save(&m2);
    QVERIFY(m2.id > 0);

    QVERIFY(m1.id != m2.id);

    XmlDao::sync();
}

void ModelXmlDaoTest::testAll()
{
    QList< Model* > lst;
    m_dao.all(&lst);
    QVERIFY(lst.count() == 2);

    m_dao.dispose(&lst);
    QVERIFY(lst.count() == 0);
}

void ModelXmlDaoTest::testFindById()
{
    Model m;
    QVERIFY(m_dao.find(Q_UINT64_C(1), &m));

    QVERIFY(m.id    == Q_UINT64_C(1));
    QVERIFY(m.kind  == Model::MODEL_SETTINGS);
    QVERIFY(m.title == "Foo settings model");
}

void ModelXmlDaoTest::testFindByKind()
{
    QList< Model* > lst;
    m_dao.findByKind(Model::MODEL_SETTINGS, &lst);
    QVERIFY(lst.count() == 1);

    Model* m = lst.at(0);

    QVERIFY(m->id    == Q_UINT64_C(1));
    QVERIFY(m->kind  == Model::MODEL_SETTINGS);
    QVERIFY(m->title == "Foo settings model");

    m_dao.dispose(&lst);
}

void ModelXmlDaoTest::testFindByTitle()
{
    QList< Model* > lst;
    m_dao.findByTitle("Foo assignment model", &lst);
    QVERIFY(lst.count() == 1);

    Model* m = lst.at(0);

    QVERIFY(m->id    == Q_UINT64_C(2));
    QVERIFY(m->kind  == Model::MODEL_AWARD_ASSIGN);
    QVERIFY(m->title == "Foo assignment model");

    m_dao.dispose(&lst);
}

void ModelXmlDaoTest::testUpdate()
{
    Model m1;
    QVERIFY(m_dao.find(Q_UINT64_C(1), &m1));

    m1.title = "Modified foo settings model";

    m_dao.update(m1);
    XmlDao::sync();

    Model m2;
    QVERIFY(m_dao.find(Q_UINT64_C(1), &m2));

    QVERIFY(m1.id    == m2.id);
    QVERIFY(m1.kind  == m2.kind);
    QVERIFY(m1.title == m2.title);
}

void ModelXmlDaoTest::testRemove()
{
    Model m1;
    QVERIFY(m_dao.find(Q_UINT64_C(2), &m1));

    m_dao.remove(m1);
    XmlDao::sync();

    Model m2;
    QVERIFY(m_dao.find(Q_UINT64_C(2), &m2) == false);
}

void ModelXmlDaoTest::cleanupTestCase()
{
    XmlDao::clearUp();
    QVERIFY(QFile::exists(m_path)==false);
}

#include "model_parameter_xml_dao_test.h"

#include <QFile>
#include <QtTest/QtTest>

ModelParameterXmlDaoTest::ModelParameterXmlDaoTest(QObject *parent)
    : QObject(parent)
{
    m_path = "parameterDaoTest.xml";
}

void ModelParameterXmlDaoTest::initTestCase()
{
    XmlDao::init(m_path);
    QVERIFY(QFile::exists(m_path));

    modelDao = new ModelXmlDao;
    modelParameterDao = new ModelParameterXmlDao;
}

void ModelParameterXmlDaoTest::testFindNone()
{
    ModelParameter* p = modelParameterDao->find(Q_UINT64_C(1));
    QVERIFY(p == NULL);
}

void ModelParameterXmlDaoTest::testSave()
{
    domain_id_t nullId = Q_UINT64_C(0);

    /** Save models */

    Model* m1 = new Model;
    m1->kind  = Model::MODEL_SETTINGS;
    m1->title = "Foo settings model";
    modelDao->save(m1);
    QVERIFY(m1->id > nullId);

    Model* m2 = new Model;
    m2->kind  = Model::MODEL_AWARD_ASSIGN;
    m2->title = "Foo assignment model";
    modelDao->save(m2);
    QVERIFY(m2->id > nullId);

    /** Save parameters */

    ModelParameter* p1 = new ModelParameter;
    p1->kind  = Domain::LOGICAL_NONE;
    p1->title = "Server name";
    p1->codeName = "SERV_NAME";
    p1->setModel(m1);
    modelParameterDao->save(p1);
    QVERIFY(p1->id > nullId);

    ModelParameter* p2 = new ModelParameter;
    p2->id    = nullId;
    p2->kind  = Domain::LOGICAL_NONE;
    p2->title = "Server description";
    p2->codeName = "SERV_DESCR";
    p2->setModel(m1);
    modelParameterDao->save(p2);
    QVERIFY(p2->id > nullId);

    ModelParameter* p3 = new ModelParameter;
    p3->id    = nullId;
    p3->kind  = Domain::LOGICAL_NONE;
    p3->title = "Foo medal";
    p3->codeName = "FOO_MEDAL";
    p3->setModel(m2);
    modelParameterDao->save(p3);
    QVERIFY(p3->id > nullId);

    ModelParameter* p4 = new ModelParameter;
    p4->id    = nullId;
    p4->kind  = Domain::LOGICAL_OR;
    p4->title = "Kill enemy aircrafts";
    p4->codeName = "KILL_ENEMY_AIR";
    p4->setParent(p3);
    modelParameterDao->save(p4);
    QVERIFY(p4->id > nullId);

    ModelParameter* p5 = new ModelParameter;
    p5->id    = nullId;
    p5->kind  = Domain::LOGICAL_OR;
    p5->title = "Kill enemy cars";
    p5->codeName = "KILL_ENEMY_CAR";
    p5->setParent(p3);
    modelParameterDao->save(p5);
    QVERIFY(p5->id > nullId);

    XmlDao::sync();
}

void ModelParameterXmlDaoTest::cleanupTestCase()
{
    delete (ModelParameterXmlDao*) modelParameterDao;
    delete (ModelXmlDao*) modelDao;

    XmlDao::clearUp();
    QVERIFY(QFile::exists(m_path)==false);
}

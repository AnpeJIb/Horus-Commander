#include "parameter_xml_dao_test.h"

#include <QFile>
#include <QtTest/QtTest>

ParameterXmlDaoTest::ParameterXmlDaoTest(QObject *parent)
    : QObject(parent)
{
    m_path = "parameterDaoTest.xml";
}

void ParameterXmlDaoTest::initTestCase()
{
    XmlDao::init(m_path);
    QVERIFY(QFile::exists(m_path));

    modelDao = new ModelXmlDao;
    parameterDao = new ParameterXmlDao;
}

void ParameterXmlDaoTest::testFindNone()
{
    Parameter* p = parameterDao->find(Q_UINT64_C(1));
    QVERIFY(p == NULL);
}

void ParameterXmlDaoTest::testSave()
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

    Parameter* p1 = new Parameter;
    p1->kind  = Domain::LOGICAL_NONE;
    p1->title = "Server name";
    p1->codeName = "SERV_NAME";
    p1->setModel(m1);
    parameterDao->save(p1);
    QVERIFY(p1->id > nullId);

    Parameter* p2 = new Parameter;
    p2->id    = nullId;
    p2->kind  = Domain::LOGICAL_NONE;
    p2->title = "Server description";
    p2->codeName = "SERV_DESCR";
    p2->setModel(m1);
    parameterDao->save(p2);
    QVERIFY(p2->id > nullId);

    Parameter* p3 = new Parameter;
    p3->id    = nullId;
    p3->kind  = Domain::LOGICAL_NONE;
    p3->title = "Foo medal";
    p3->codeName = "FOO_MEDAL";
    p3->setModel(m2);
    parameterDao->save(p3);
    QVERIFY(p3->id > nullId);

    Parameter* p4 = new Parameter;
    p4->id    = nullId;
    p4->kind  = Domain::LOGICAL_OR;
    p4->title = "Kill enemy aircrafts";
    p4->codeName = "KILL_ENEMY_AIR";
    p4->setParent(p3);
    parameterDao->save(p4);
    QVERIFY(p4->id > nullId);

    Parameter* p5 = new Parameter;
    p5->id    = nullId;
    p5->kind  = Domain::LOGICAL_OR;
    p5->title = "Kill enemy cars";
    p5->codeName = "KILL_ENEMY_CAR";
    p5->setParent(p3);
    parameterDao->save(p5);
    QVERIFY(p5->id > nullId);

    XmlDao::sync();
}

void ParameterXmlDaoTest::cleanupTestCase()
{
    delete (ParameterXmlDao*) parameterDao;
    delete (ModelXmlDao*) modelDao;

    XmlDao::clearUp();
    QVERIFY(QFile::exists(m_path)==false);
}

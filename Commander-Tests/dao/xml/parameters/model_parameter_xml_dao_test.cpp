#include "model_parameter_xml_dao_test.h"

#include <QFile>
#include <QtTest/QtTest>

ModelParameterXmlDaoTest::ModelParameterXmlDaoTest(QObject *parent)
    : QObject(parent)
{
    m_path = "modelParameterDaoTest.xml";
}

void ModelParameterXmlDaoTest::initTestCase()
{
    XmlDaoBase::init(m_path);
    QVERIFY(QFile::exists(m_path));

    modelDao = new ModelXmlDao;
    modelParameterDao = new ModelParameterXmlDao;
    simpleParameterDao = new SimpleParameterXmlDao;
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

    /** Save simple parameters */

    SimpleParameter* sp1 = new SimpleParameter;
    sp1->codeName = "SRV_NAME";
    sp1->title = "Server name";
    simpleParameterDao->save(sp1);
    QVERIFY(sp1->id > nullId);

    SimpleParameter* sp2 = new SimpleParameter;
    sp2->codeName = "SRV_DESCR";
    sp2->title = "Server description";
    simpleParameterDao->save(sp2);
    QVERIFY(sp2->id > nullId);

    SimpleParameter* sp3 = new SimpleParameter;
    sp3->codeName = "KILL_EAIR";
    sp3->title = "Kill enemy aircrafts";
    simpleParameterDao->save(sp3);
    QVERIFY(sp3->id > nullId);

    SimpleParameter* sp4 = new SimpleParameter;
    sp4->codeName = "KILL_ECAR";
    sp4->title = "Kill enemy cars";
    simpleParameterDao->save(sp4);
    QVERIFY(sp4->id > nullId);

    /** Save model parameters */

    ModelParameter* mp1 = new ModelParameter;
    mp1->kind  = Domain::LOGICAL_NONE;
    mp1->title = "Server name";
    mp1->setModel(m1);
    mp1->setSimpleParameter(sp1);
    modelParameterDao->save(mp1);
    QVERIFY(mp1->id > nullId);

    ModelParameter* mp2 = new ModelParameter;
    mp2->kind  = Domain::LOGICAL_NONE;
    mp2->title = "Server description";
    mp2->setModel(m1);
    mp2->setSimpleParameter(sp2);
    modelParameterDao->save(mp2);
    QVERIFY(mp2->id > nullId);

    ModelParameter* mp3 = new ModelParameter;
    mp3->kind  = Domain::LOGICAL_OR;
    mp3->title = "Kill enemy aircrafts or cars";
    mp3->setModel(m2);
    modelParameterDao->save(mp3);
    QVERIFY(mp3->id > nullId);

    ModelParameter* mp4 = new ModelParameter;
    mp4->kind  = Domain::LOGICAL_NONE;
    mp4->title = "Kill enemy aircrafts";
    mp4->setParent(mp3);
    mp4->setSimpleParameter(sp3);
    modelParameterDao->save(mp4);
    QVERIFY(mp4->id > nullId);

    ModelParameter* mp5 = new ModelParameter;
    mp5->kind  = Domain::LOGICAL_NONE;
    mp5->title = "Kill enemy cars";
    mp5->setParent(mp3);
    mp5->setSimpleParameter(sp4);
    modelParameterDao->save(mp5);
    QVERIFY(mp5->id > nullId);

    XmlDaoBase::sync();
}

void ModelParameterXmlDaoTest::cleanupTestCase()
{
    delete (SimpleParameterXmlDao*) simpleParameterDao;
    delete (ModelParameterXmlDao*)  modelParameterDao;
    delete (ModelXmlDao*) modelDao;

    XmlDaoBase::clearUp();
    QVERIFY(QFile::exists(m_path)==false);
}

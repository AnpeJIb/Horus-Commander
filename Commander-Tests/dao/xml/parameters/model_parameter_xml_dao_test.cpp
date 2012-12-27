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

    ModelParameter* mp1 = new ModelParameter(modelParameterDao);
    mp1->kind  = Domain::LOGICAL_NONE;
    mp1->title = "Server name";
    mp1->setModel(m1);
    mp1->setSimpleParameter(sp1);
    modelParameterDao->save(mp1);
    QVERIFY(mp1->id > nullId);

    ModelParameter* mp2 = new ModelParameter(modelParameterDao);
    mp2->kind  = Domain::LOGICAL_NONE;
    mp2->title = "Server description";
    mp2->setModel(m1);
    mp2->setSimpleParameter(sp2);
    modelParameterDao->save(mp2);
    QVERIFY(mp2->id > nullId);

    ModelParameter* mp3 = new ModelParameter(modelParameterDao);
    mp3->kind  = Domain::LOGICAL_OR;
    mp3->title = "Foo medal requirements";
    mp3->setModel(m2);
    modelParameterDao->save(mp3);
    QVERIFY(mp3->id > nullId);

    ModelParameter* mp4 = new ModelParameter(modelParameterDao);
    mp4->kind  = Domain::LOGICAL_NONE;
    mp4->title = "Kill enemy aircrafts";
    mp4->setParent(mp3);
    mp4->setSimpleParameter(sp3);
    modelParameterDao->save(mp4);
    QVERIFY(mp4->id > nullId);

    ModelParameter* mp5 = new ModelParameter(modelParameterDao);
    mp5->kind  = Domain::LOGICAL_NONE;
    mp5->title = "Kill enemy cars";
    mp5->setParent(mp3);
    mp5->setSimpleParameter(sp4);
    modelParameterDao->save(mp5);
    QVERIFY(mp5->id > nullId);

    XmlDaoBase::sync();

    delete mp1;
    delete mp2;
    delete mp3;
    delete mp4;
    delete mp5;

    delete sp1;
    delete sp2;
    delete sp3;
    delete sp4;

    delete m1;
    delete m2;

    ModelParameterXmlDao::clearCache();
    ModelXmlDao::clearCache();
    SimpleParameterDao::clearCache();
}

void ModelParameterXmlDaoTest::testAll()
{
    QList< ModelParameter* > lst;
    modelParameterDao->all(&lst);
    QVERIFY(lst.count() == 5);
}

void ModelParameterXmlDaoTest::testFindById()
{
    /** Test Model Parameter 1 */

    ModelParameter* mp1 = modelParameterDao->find(Q_UINT64_C(1));

    QVERIFY(mp1 != NULL);
    QVERIFY(mp1->id    == Q_UINT64_C(1));
    QVERIFY(mp1->title == "Server name");
    QVERIFY(mp1->kind  == Domain::LOGICAL_NONE);

    Model* m1 = mp1->model();

    QVERIFY(m1 != NULL);
    QVERIFY(m1->id    == Q_UINT64_C(1));
    QVERIFY(m1->kind  == Model::MODEL_SETTINGS);
    QVERIFY(m1->title == "Foo settings model");

    SimpleParameter* sp1 = mp1->simpleParameter();

    QVERIFY(sp1 != NULL);
    QVERIFY(sp1->id       == Q_UINT64_C(1));
    QVERIFY(sp1->title    == "Server name");
    QVERIFY(sp1->codeName == "SRV_NAME");

    QVERIFY(mp1->parent() == NULL);

    /** Test Model Parameter 2 */

    ModelParameter* mp2 = modelParameterDao->find(Q_UINT64_C(2));

    QVERIFY(mp2 != NULL);
    QVERIFY(mp2->id    == Q_UINT64_C(2));
    QVERIFY(mp2->title == "Server description");
    QVERIFY(mp2->kind  == Domain::LOGICAL_NONE);

    Model* m2 = mp2->model();

    QVERIFY(m2 != NULL);
    QVERIFY(m2->id == Q_UINT64_C(1));

    SimpleParameter* sp2 = mp2->simpleParameter();

    QVERIFY(sp2 != NULL);
    QVERIFY(sp2->id       == Q_UINT64_C(2));
    QVERIFY(sp2->title    == "Server description");
    QVERIFY(sp2->codeName == "SRV_DESCR");

    QVERIFY(mp2->parent() == NULL);

    /** Test Model Parameter 3 */

    ModelParameter* mp3 = modelParameterDao->find(Q_UINT64_C(3));

    QVERIFY(mp3 != NULL);
    QVERIFY(mp3->id    == Q_UINT64_C(3));
    QVERIFY(mp3->title == "Foo medal requirements");
    QVERIFY(mp3->kind  == Domain::LOGICAL_OR);

    Model* m3 = mp3->model();

    QVERIFY(m3 != NULL);
    QVERIFY(m3->id == Q_UINT64_C(2));

    SimpleParameter* sp3 = mp3->simpleParameter();

    QVERIFY(sp3 == NULL);
    QVERIFY(mp3->parent() == NULL);

    /** Test Model Parameter 4 */

    ModelParameter* mp4 = modelParameterDao->find(Q_UINT64_C(4));

    QVERIFY(mp4 != NULL);
    QVERIFY(mp4->id    == Q_UINT64_C(4));
    QVERIFY(mp4->title == "Kill enemy aircrafts");
    QVERIFY(mp4->kind  == Domain::LOGICAL_NONE);

    Model* m4 = mp4->model();

    QVERIFY(m4 != NULL);
    QVERIFY(m4->id == Q_UINT64_C(2));

    SimpleParameter* sp4 = mp4->simpleParameter();

    QVERIFY(sp4 != NULL);
    QVERIFY(sp4->id       == Q_UINT64_C(3));
    QVERIFY(sp4->title    == "Kill enemy aircrafts");
    QVERIFY(sp4->codeName == "KILL_EAIR");

    QVERIFY(mp4->parent() == mp3);

    /** Test Model Parameter 5 */

    ModelParameter* mp5 = modelParameterDao->find(Q_UINT64_C(5));

    QVERIFY(mp5 != NULL);
    QVERIFY(mp5->id    == Q_UINT64_C(5));
    QVERIFY(mp5->title == "Kill enemy cars");
    QVERIFY(mp5->kind  == Domain::LOGICAL_NONE);

    Model* m5 = mp5->model();

    QVERIFY(m5 != NULL);
    QVERIFY(m5->id == Q_UINT64_C(2));

    SimpleParameter* sp5 = mp5->simpleParameter();

    QVERIFY(sp5 != NULL);
    QVERIFY(sp5->id       == Q_UINT64_C(4));
    QVERIFY(sp5->title    == "Kill enemy cars");
    QVERIFY(sp5->codeName == "KILL_ECAR");

    QVERIFY(mp5->parent() == mp3);
}

void ModelParameterXmlDaoTest::testReferentialIntegrity()
{
    domain_id_t id = Q_UINT64_C(1);

    ModelParameter* mp1;
    mp1 = modelParameterDao->find(id);

    ModelParameter* mp2;
    mp2 = modelParameterDao->find(id);

    QVERIFY(mp1 == mp2);
}

void ModelParameterXmlDaoTest::testFindByTitle()
{
    domain_id_t id = Q_UINT64_C(1);
    QList< ModelParameter* > lst;

    modelParameterDao->findByTitle("Server name", &lst);
    QVERIFY(lst.count() == 1);

    ModelParameter* mp1 = lst.at(0);

    QVERIFY(mp1->id    == id);
    QVERIFY(mp1->kind  == Domain::LOGICAL_NONE);
    QVERIFY(mp1->title == "Server name");

    ModelParameter* mp2 = modelParameterDao->find(id);
    QVERIFY(mp1 == mp2);
}

void ModelParameterXmlDaoTest::testFindByKind()
{
    domain_id_t id = Q_UINT64_C(1);
    QList< ModelParameter* > lst;

    modelParameterDao->findByKind(Domain::LOGICAL_NONE, &lst);
    QVERIFY(lst.count() == 4);

    ModelParameter* mp1 = lst.at(0);

    QVERIFY(mp1->id    == id);
    QVERIFY(mp1->kind  == Domain::LOGICAL_NONE);
    QVERIFY(mp1->title == "Server name");

    ModelParameter* mp2 = modelParameterDao->find(id);
    QVERIFY(mp1 == mp2);
}

void ModelParameterXmlDaoTest::testFindByParent()
{
    ModelParameterXmlDao::clearCacheAndDisposeDomains();

    ModelParameter* parent = modelParameterDao->find(Q_UINT64_C(3));
    QVERIFY(parent != NULL);

    QList< ModelParameter* > lst;
    modelParameterDao->findByParent(parent, &lst);
    QVERIFY(lst.count() == 2);

    ModelParameter* child = modelParameterDao->find(Q_UINT64_C(4));

    QVERIFY(child == lst.at(0));
    QVERIFY(child->parent() == parent);
}

void ModelParameterXmlDaoTest::testFindByModel()
{
    Model* m = modelDao->find(Q_UINT64_C(1));
    QVERIFY(m != NULL);

    QList< ModelParameter* > lst;
    modelParameterDao->findByModel(m, &lst);
    QVERIFY(lst.count() == 2);

    ModelParameter* mp1 = lst.at(0);
    ModelParameter* mp2 = modelParameterDao->find(Q_UINT64_C(1));

    QVERIFY(mp2 != NULL);
    QVERIFY(mp1 == mp2);
}

void ModelParameterXmlDaoTest::testFindBySimpleParameter()
{
    SimpleParameter* sp = simpleParameterDao->find(Q_UINT64_C(1));
    QVERIFY(sp != NULL);

    QList< ModelParameter* > lst;
    modelParameterDao->findBySimpleParameter(sp, &lst);
    QVERIFY(lst.count() == 1);

    ModelParameter* mp1 = lst.at(0);
    ModelParameter* mp2 = modelParameterDao->find(Q_UINT64_C(1));

    QVERIFY(mp2 != NULL);
    QVERIFY(mp1 == mp2);
}

void ModelParameterXmlDaoTest::testFindXmlNode()
{
    QDomNode node;

    node = ((ModelParameterXmlDao*) modelParameterDao)->findXmlNode(Q_UINT64_C(0));
    QVERIFY(node.isNull());

    node = ((ModelParameterXmlDao*) modelParameterDao)->findXmlNode(Q_UINT64_C(1));
    QVERIFY(node.isNull()==false);

    node = ((ModelParameterXmlDao*) modelParameterDao)->findXmlNode(Q_UINT64_C(2));
    QVERIFY(node.isNull()==false);

    node = ((ModelParameterXmlDao*) modelParameterDao)->findXmlNode(Q_UINT64_C(3));
    QVERIFY(node.isNull()==false);

    node = ((ModelParameterXmlDao*) modelParameterDao)->findXmlNode(Q_UINT64_C(4));
    QVERIFY(node.isNull()==false);

    node = ((ModelParameterXmlDao*) modelParameterDao)->findXmlNode(Q_UINT64_C(5));
    QVERIFY(node.isNull()==false);
}

void ModelParameterXmlDaoTest::testUpdate()
{
    domain_id_t id = Q_UINT64_C(1);

    ModelParameter* mp1 = modelParameterDao->find(id);
    QVERIFY(mp1 != NULL);

    ModelParameter* mp2 = modelParameterDao->find(Q_UINT64_C(3));
    QVERIFY(mp2 != NULL);

    mp1->setParent(mp2);
    mp1->title = "Modified server name";
    modelParameterDao->update(mp1);

    XmlDaoBase::sync();
    ModelParameterXmlDao::clearCache();
    QList<ModelParameter* > lst;
    modelParameterDao->all(&lst);

    ModelParameter* mp3 = modelParameterDao->find(id);

    QVERIFY(mp3 != NULL);
    QVERIFY(mp3->title != "Server name");

    QVERIFY(mp1->id    == mp3->id);
    QVERIFY(mp1->kind  == mp3->kind);
    QVERIFY(mp1->title == mp3->title);
    QVERIFY(mp1->parent()->id == mp3->parent()->id);
    QVERIFY(mp1->model()      == mp3->model());
    QVERIFY(mp1->simpleParameter() == mp3->simpleParameter());
}

void ModelParameterXmlDaoTest::testRemove()
{
    domain_id_t id = Q_UINT64_C(1);

    ModelParameter* mp1 = modelParameterDao->find(id);
    QVERIFY(mp1 != NULL);

    modelParameterDao->remove(mp1);
    XmlDaoBase::sync();

    ModelParameter* mp2 = modelParameterDao->find(id);
    QVERIFY(mp2 == NULL);
}

void ModelParameterXmlDaoTest::cleanupTestCase()
{
    ModelXmlDao::clearCacheAndDisposeDomains();
    SimpleParameterXmlDao::clearCacheAndDisposeDomains();
    ModelParameterXmlDao::clearCacheAndDisposeDomains();

    ModelXmlDao::resetCurrentId();
    SimpleParameterXmlDao::resetCurrentId();
    ModelParameterXmlDao::resetCurrentId();

    delete (SimpleParameterXmlDao*) simpleParameterDao;
    delete (ModelParameterXmlDao*)  modelParameterDao;
    delete (ModelXmlDao*) modelDao;

    XmlDaoBase::clearUp();
    QVERIFY(QFile::exists(m_path)==false);
}


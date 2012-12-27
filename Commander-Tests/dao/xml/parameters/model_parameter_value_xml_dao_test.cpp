#include "model_parameter_value_xml_dao_test.h"

#include <QFile>
#include <QtTest/QtTest>

ModelParameterValueXmlDaoTest::ModelParameterValueXmlDaoTest(QObject *parent)
    : QObject(parent)
{
    m_path = "modelParameterValueDaoTest.xml";
}

void ModelParameterValueXmlDaoTest::initTestCase()
{
    XmlDaoBase::init(m_path);
    QVERIFY(QFile::exists(m_path));

    modelDao = new ModelXmlDao;
    simpleParameterDao = new SimpleParameterXmlDao;
    modelParameterDao = new ModelParameterXmlDao;
    schemeDao = new SchemeXmlDao;
    valueDao = new ModelParameterValueXmlDao;
}

void ModelParameterValueXmlDaoTest::testFindNone()
{
    ModelParameterValue* v = valueDao->find(Q_UINT64_C(1));
    QVERIFY(v == NULL);
}

void ModelParameterValueXmlDaoTest::testSave()
{
    domain_id_t nullId = Q_UINT64_C(0);

    Model* m = new Model;
    m->kind = Model::MODEL_SETTINGS;
    m->title = "Initial settings";
    modelDao->save(m);
    QVERIFY(m->id > nullId);

    SimpleParameter* sp1 = new SimpleParameter;
    sp1->title    = "Server name";
    sp1->codeName = "SRV_NAME";
    simpleParameterDao->save(sp1);
    QVERIFY(sp1->id > nullId);

    SimpleParameter* sp2 = new SimpleParameter;
    sp2->title    = "Server description";
    sp2->codeName = "SRV_DESCR";
    simpleParameterDao->save(sp2);
    QVERIFY(sp2->id > nullId);

    ModelParameter* mp1 = new ModelParameter(modelParameterDao);
    mp1->kind = Domain::LOGICAL_AND;
    mp1->setModel(m);
    mp1->title = "General";
    modelParameterDao->save(mp1);
    QVERIFY(mp1->id > nullId);

    ModelParameter* mp2 = new ModelParameter(modelParameterDao);
    mp2->kind = Domain::LOGICAL_NONE;
    mp2->setParent(mp1);
    mp2->setSimpleParameter(sp1);
    mp2->title = sp1->title;
    modelParameterDao->save(mp2);
    QVERIFY(mp2->id > nullId);

    ModelParameter* mp3 = new ModelParameter(modelParameterDao);
    mp3->kind = Domain::LOGICAL_NONE;
    mp3->setParent(mp1);
    mp3->setSimpleParameter(sp2);
    mp3->title = sp2->title;
    modelParameterDao->save(mp3);
    QVERIFY(mp3->id > nullId);

    Scheme* sch = new Scheme(schemeDao);
    sch->title = "Default";
    sch->description = "Default initial settings";
    sch->setModel(m);
    schemeDao->save(sch);
    QVERIFY(sch->id > nullId);

    ModelParameterValue* v1 = new ModelParameterValue(valueDao);
    v1->setScheme(sch);
    v1->setParameter(mp2);
    v1->value = "My nice server";
    valueDao->save(v1);
    QVERIFY(v1->id > nullId);

    ModelParameterValue* v2 = new ModelParameterValue(valueDao);
    v2->setScheme(sch);
    v2->setParameter(mp3);
    v2->value = "Really nice server";
    valueDao->save(v2);
    QVERIFY(v2->id > nullId);

    XmlDaoBase::sync();

    delete v1;
    delete v2;

    delete sch;

    delete mp1;
    delete mp2;
    delete mp3;

    delete sp1;
    delete sp2;

    delete m;

    ModelParameterValueXmlDao::clearCache();
    SchemeXmlDao::clearCache();
    ModelParameterXmlDao::clearCache();
    SimpleParameterXmlDao::clearCache();
    ModelXmlDao::clearCache();
}

void ModelParameterValueXmlDaoTest::testAll()
{
    QList< ModelParameterValue* > lst;
    valueDao->all(&lst);
    QVERIFY(lst.count() == 2);
}

void ModelParameterValueXmlDaoTest::testFindById()
{
    /** Test Value 1 */

    ModelParameterValue* v1 = valueDao->find(Q_UINT64_C(1));

    QVERIFY(v1 != NULL);
    QVERIFY(v1->id    == Q_UINT64_C(1));
    QVERIFY(v1->value == "My nice server");

    Scheme* sch1 = v1->scheme();
    QVERIFY(sch1 != NULL);
    QVERIFY(sch1->title == "Default");

    ModelParameter* mp1 = v1->parameter();
    QVERIFY(mp1 != NULL);
    QVERIFY(mp1->title == "Server name");

    /** Test Value 2 */

    ModelParameterValue* v2 = valueDao->find(Q_UINT64_C(2));

    QVERIFY(v2 != NULL);
    QVERIFY(v2->id    == Q_UINT64_C(2));
    QVERIFY(v2->value == "Really nice server");

    Scheme* sch2 = v2->scheme();
    QVERIFY(sch2 != NULL);
    QVERIFY(sch2 == sch1);

    ModelParameter* mp2 = v2->parameter();
    QVERIFY(mp2 != NULL);
    QVERIFY(mp2->title == "Server description");
}

void ModelParameterValueXmlDaoTest::testReferentialIntegrity()
{
    domain_id_t id = Q_UINT64_C(1);

    ModelParameterValue* v1 = valueDao->find(id);
    ModelParameterValue* v2 = valueDao->find(id);

    QVERIFY(v1 == v2);
}

void ModelParameterValueXmlDaoTest::testFindByScheme()
{
    domain_id_t id = Q_UINT64_C(1);

    Scheme* sch = schemeDao->find(Q_UINT64_C(1));
    QVERIFY(sch != NULL);

    QList< ModelParameterValue* > lst;
    valueDao->findByScheme(sch, &lst);
    QVERIFY(lst.count() == 2);

    ModelParameterValue* v1 = lst.at(0);
    QVERIFY(v1->id == id);

    ModelParameterValue* v2 = valueDao->find(id);
    QVERIFY(v1 == v2);
}

void ModelParameterValueXmlDaoTest::testFindByParameter()
{
    domain_id_t id = Q_UINT64_C(1);

    ModelParameter* mp = modelParameterDao->find(Q_UINT64_C(2));
    QVERIFY(mp != NULL);

    QList< ModelParameterValue* > lst;
    valueDao->findByModelParameter(mp, &lst);
    QVERIFY(lst.count() == 1);

    ModelParameterValue* v1 = lst.at(0);
    QVERIFY(v1->id == id);

    ModelParameterValue* v2 = valueDao->find(id);
    QVERIFY(v1 == v2);
}

void ModelParameterValueXmlDaoTest::testFindByValue()
{
    domain_id_t id = Q_UINT64_C(1);

    QList< ModelParameterValue* > lst;
    valueDao->findByValue("My nice server", &lst);
    QVERIFY(lst.count() == 1);

    ModelParameterValue* v1 = lst.at(0);
    QVERIFY(v1->id == id);

    ModelParameterValue* v2 = valueDao->find(id);
    QVERIFY(v1 == v2);
}

void ModelParameterValueXmlDaoTest::testUpdate()
{
    domain_id_t id = Q_UINT64_C(1);

    ModelParameterValue* v1 = valueDao->find(id);
    QVERIFY(v1 != NULL);

    Scheme* sch1 = v1->scheme();
    QVERIFY(sch1 != NULL);

    Scheme* sch2 = new Scheme(schemeDao);
    sch2->setModel(sch1->model());
    sch2->title = "Custom";
    sch2->description = "My custom settings scheme";
    schemeDao->save(sch2);
    QVERIFY(sch2->id > Q_UINT64_C(0));

    v1->value = "Better server";
    v1->setScheme(sch2);
    valueDao->update(v1);

    XmlDaoBase::sync();
    ModelParameterValueXmlDao::clearCache();
    QList<ModelParameterValue* > lst;
    valueDao->all(&lst);

    ModelParameterValue* v2 = valueDao->find(id);

    QVERIFY(v2 != NULL);
    QVERIFY(v2->value != "My nice server");

    QVERIFY(v1->id    == v2->id);
    QVERIFY(v1->value == v2->value);
    QVERIFY(v1->scheme()    == v2->scheme());
    QVERIFY(v1->parameter() == v2->parameter());
}

void ModelParameterValueXmlDaoTest::testRemove()
{
    domain_id_t id = Q_UINT64_C(2);

    ModelParameterValue* v1 = valueDao->find(id);
    QVERIFY(v1 != NULL);

    valueDao->remove(v1);
    XmlDaoBase::sync();

    ModelParameterValue* v2 = valueDao->find(id);
    QVERIFY(v2 == NULL);
}

void ModelParameterValueXmlDaoTest::cleanupTestCase()
{
    ModelParameterValueXmlDao::clearCacheAndDisposeDomains();
    SchemeXmlDao::clearCacheAndDisposeDomains();
    ModelParameterXmlDao::clearCacheAndDisposeDomains();
    SimpleParameterXmlDao::clearCacheAndDisposeDomains();
    ModelXmlDao::clearCacheAndDisposeDomains();

    ModelParameterValueXmlDao::resetCurrentId();
    SchemeXmlDao::resetCurrentId();
    ModelParameterXmlDao::resetCurrentId();
    SimpleParameterXmlDao::resetCurrentId();
    ModelXmlDao::resetCurrentId();

    delete (ModelParameterValueXmlDao*) valueDao;
    delete (SchemeXmlDao*) schemeDao;
    delete (ModelParameterXmlDao*) modelParameterDao;
    delete (SimpleParameterXmlDao*) simpleParameterDao;
    delete (ModelXmlDao*) modelDao;

    XmlDaoBase::clearUp();
    QVERIFY(QFile::exists(m_path)==false);
}

#ifndef MODEL_PARAMETER_VALUE_XML_DAO_TEST_H
#define MODEL_PARAMETER_VALUE_XML_DAO_TEST_H

#include <QObject>
#include <QString>

#include "model_xml_dao.h"
#include "simple_parameter_xml_dao.h"
#include "model_parameter_xml_dao.h"
#include "scheme_carrier_xml_dao.h"
#include "model_parameter_value_xml_dao.h"

using namespace Dao;
using namespace Dao::Parameters;

class ModelParameterValueXmlDaoTest: public QObject
{
    Q_OBJECT
public:
    explicit ModelParameterValueXmlDaoTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void testFindNone();
    void testSave();
    void testAll();
    void testFindById();
    void testReferentialIntegrity();
    void testFindByScheme();
    void testFindByParameter();
    void testFindByValue();
    void testUpdate();
    void testRemove();
    void cleanupTestCase();

private:
    QString m_path;

    ModelDao* modelDao;
    SimpleParameterDao* simpleParameterDao;
    ModelParameterDao* modelParameterDao;
    SchemeDao* schemeDao;
    ModelParameterValueDao* valueDao;
};

#endif // MODEL_PARAMETER_VALUE_XML_DAO_TEST_H

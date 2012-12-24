#ifndef SIMPLE_PARAMETER_XML_DAO_TEST_H
#define SIMPLE_PARAMETER_XML_DAO_TEST_H

#include <QObject>
#include <QString>
#include "simple_parameter_xml_dao.h"

using namespace Dao;
using namespace Dao::Parameters;

class SimpleParameterXmlDaoTest: public QObject
{
    Q_OBJECT
public:
    explicit SimpleParameterXmlDaoTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void testFindNone();
    void testSave();
    void testAll();
    void testFindById();
    void testReferentialIntegrity();
    void testFindByCodeName();
    void testFindByTitle();
    void testFindXmlNode();
    void testUpdate();
    void testRemove();
    void cleanupTestCase();

private:
    QString m_path;
    SimpleParameterDao* dao;
};

#endif // SIMPLE_PARAMETER_XML_DAO_TEST_H

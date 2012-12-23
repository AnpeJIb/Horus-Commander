#ifndef PARAMETER_XML_DAO_TEST_H
#define PARAMETER_XML_DAO_TEST_H

#include <QObject>
#include <QString>
#include "model_parameter_xml_dao.h"
#include "model_xml_dao.h"

using namespace Dao;
using namespace Dao::Parameters;

class ModelParameterXmlDaoTest: public QObject
{
    Q_OBJECT
public:
    explicit ModelParameterXmlDaoTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void testFindNone();
    void testSave();
    void cleanupTestCase();

private:
    QString m_path;
    ModelParameterDao* modelParameterDao;
    ModelDao* modelDao;
};

#endif // PARAMETER_XML_DAO_TEST_H

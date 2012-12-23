#ifndef PARAMETER_XML_DAO_TEST_H
#define PARAMETER_XML_DAO_TEST_H

#include <QObject>
#include <QString>
#include "parameter_xml_dao.h"
#include "model_xml_dao.h"

using namespace Dao;
using namespace Dao::Parameters;

class ParameterXmlDaoTest: public QObject
{
    Q_OBJECT
public:
    explicit ParameterXmlDaoTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void testFindNone();
    void testSave();
    void cleanupTestCase();

private:
    QString m_path;
    ParameterDao* parameterDao;
    ModelDao* modelDao;
};

#endif // PARAMETER_XML_DAO_TEST_H

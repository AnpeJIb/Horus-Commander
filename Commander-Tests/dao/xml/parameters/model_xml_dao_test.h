#ifndef MODEL_XML_DAO_TEST_H
#define MODEL_XML_DAO_TEST_H

#include <QObject>
#include <QString>
#include "model_xml_dao.h"

using namespace Dao;
using namespace Dao::Parameters;

class ModelXmlDaoTest: public QObject
{
    Q_OBJECT
public:
    explicit ModelXmlDaoTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void testFindNone();
    void testSave();
    void testFindById();
    void testFindByKind();
    void testFindByTitle();
    void testUpdate();
    void testRemove();
    void cleanupTestCase();

private:
    QString m_path;
    ModelXmlDao m_dao;
};

#endif // MODEL_XML_DAO_TEST_H

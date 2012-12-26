#ifndef SCHEME_XML_DAO_TEST_H
#define SCHEME_XML_DAO_TEST_H

#include <QObject>
#include <QString>
#include "scheme_xml_dao.h"

using namespace Dao;
using namespace Dao::Parameters;

class SchemeXmlDaoTest: public QObject
{
    Q_OBJECT
public:
    explicit SchemeXmlDaoTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void testFindNone();
    void testSave();
    void testAll();
    void testFindById();
    void testReferentialIntegrity();
    void testFindByTitle();
    void testFindByDescription();
    void testFindByModel();
    void testFindXmlNode();
    void testUpdate();
    void testRemove();
    void cleanupTestCase();

private:
    QString m_path;
    SchemeDao* schemeDao;
    ModelDao* modelDao;
};

#endif // SCHEME_XML_DAO_TEST_H

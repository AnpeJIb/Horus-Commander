#ifndef PRIMARY_CONFIG_SERVICE_TEST_H
#define PRIMARY_CONFIG_SERVICE_TEST_H

#include <QObject>
#include <QString>

class PrimaryConfigServiceTest: public QObject
{
    Q_OBJECT
public:
    explicit PrimaryConfigServiceTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void testGetAllSchemes();
    void cleanupConfig();
    void testSchemeFind();
    void cleanupTestCase();

private:
    QString configPath;
    QString dsPath;
};

#endif // PRIMARY_CONFIG_SERVICE_TEST_H

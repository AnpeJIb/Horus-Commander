#ifndef PRIMARY_CONFIG_HELPER_TEST_H
#define PRIMARY_CONFIG_HELPER_TEST_H

#include <QObject>
#include <QString>

class PrimaryConfigHelperTest: public QObject
{
    Q_OBJECT
public:
    explicit PrimaryConfigHelperTest(QObject *parent = 0);

private slots:
    void initTestCase();
    void testScheme();
    void cleanupTestCase();

private:
    QString configPath;
    QString dsPath;
};

#endif // PRIMARY_CONFIG_HELPER_TEST_H

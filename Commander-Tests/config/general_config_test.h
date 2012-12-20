#ifndef GENERAL_CONFIG_TEST_H
#define GENERAL_CONFIG_TEST_H

#include <QObject>

class GeneralConfigTest: public QObject
{
    Q_OBJECT
public:
    explicit GeneralConfigTest(QObject *parent = 0);

private slots:
    void initTestCase();

    void testLangCode();

    void cleanupTestCase();
};

#endif // GENERAL_CONFIG_TEST_H

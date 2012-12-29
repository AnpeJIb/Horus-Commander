#ifndef SYSTEM_PATH_TEST_H
#define SYSTEM_PATH_TEST_H

#include <QObject>
#include <QString>

class SystemPathTest: public QObject
{
    Q_OBJECT
public:
    explicit SystemPathTest(QObject *parent = 0);

private slots:
    void testSystemDirPath();
    void testConfigPath();
    void testDataSourcePath();
    void testLogPath();

private:
    QString systemPath;
};

#endif // SYSTEM_PATH_TEST_H

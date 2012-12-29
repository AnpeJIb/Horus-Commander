#include "system_path_test.h"
#include "system_path.h"

#include <QDir>
#include <QtTest/QtTest>

SystemPathTest::SystemPathTest(QObject *parent)
    : QObject(parent)
{
    systemPath = QDir::homePath().append(QDir::separator()).append(".horusCommander").append(QDir::separator());
}

void SystemPathTest::testSystemDirPath()
{
    QCOMPARE(systemPath, Path::System::appDataDir());
}

void SystemPathTest::testConfigPath()
{
    QString path = QString(systemPath).append("config.ini");
    QCOMPARE(path, Path::System::config());
}

void SystemPathTest::testDataSourcePath()
{
    QString path = QString(systemPath).append("data.xml");
    QCOMPARE(path, Path::System::dataSource());
}

void SystemPathTest::testLogPath()
{
    QString path = QString(systemPath).append("system.log");
    QCOMPARE(path, Path::System::log());
}

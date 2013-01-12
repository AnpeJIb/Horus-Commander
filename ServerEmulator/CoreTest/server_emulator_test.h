#ifndef SERVER_EMULATOR_TEST_H
#define SERVER_EMULATOR_TEST_H

#include <QObject>
#include <QString>
#include <QWaitCondition>
#include <QMutex>

#include "server_emulator.h"
#include "expected_strings.h"

class ServerEmulatorTest : public QObject
{
    Q_OBJECT
public:
    explicit ServerEmulatorTest(QObject *parent = 0);

public slots:
    void onStartSuccess();
    void onPrintToConsoleCalled(const QString& msg);
    
private slots:
    void initTestCase();
    void testStartFail();
    void testStartSuccess();
    void cleanupTestCase();

private:
    ServerEmulator m_emulator;
    QWaitCondition m_condition;
    QMutex m_mutex;
    ExpectedStrings m_console_expected_strings;
};

#endif // SERVER_EMULATOR_TEST_H

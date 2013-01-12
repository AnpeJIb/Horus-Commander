#include "server_emulator_test.h"

#include <QtTest/QtTest>

ServerEmulatorTest::ServerEmulatorTest(QObject *parent) :
    QObject(parent)
{
}

void ServerEmulatorTest::initTestCase()
{
    connect(&m_emulator, SIGNAL(startSuccess()),
            this, SLOT(onStartSuccess()), Qt::DirectConnection);
    connect(&m_emulator, SIGNAL(printToConsoleCalled(QString)),
            this, SLOT(onPrintToConsoleCalled(const QString&)), Qt::DirectConnection);

    m_console_expected_strings.reset();

    m_console_expected_strings.append("IL-2 Horus Team: IL-2 FB dedicated server emulator");
    m_console_expected_strings.append("  *** Library **** DT ****  Loaded *** XXX");
    m_console_expected_strings.append("RTS Version Y.Y");
    m_console_expected_strings.append("Core Version Z.Z");
    m_console_expected_strings.append("Sound: Native library (build Q.Q, target - TTTT) loaded.");
    m_console_expected_strings.append("IL2 FB dedicated server vAA.BB.CC");
}

void ServerEmulatorTest::testStartFail()
{
    m_emulator.configure("99.88.77.66", "10", "events.log");
    m_emulator.start();
    m_emulator.wait();

    QCOMPARE(m_emulator.exitResult(), ServerEmulator::START_FAILED);
}

void ServerEmulatorTest::testStartSuccess()
{
    m_console_expected_strings.resetIndex();

    m_emulator.configure("127.0.0.1", "20001", "events.log");
    m_emulator.start();

    m_mutex.lock();
    m_condition.wait(&m_mutex);
    m_mutex.unlock();

    QCOMPARE(m_emulator.exitResult(), ServerEmulator::UNDEFINED);
    QVERIFY(m_console_expected_strings.areAllSucceded());
}

void ServerEmulatorTest::cleanupTestCase()
{
    m_emulator.stop();
    m_emulator.wait();

    QCOMPARE(m_emulator.exitResult(), ServerEmulator::STOPPED_NORMALLY);
}

void ServerEmulatorTest::onStartSuccess()
{
    m_mutex.lock();
    m_condition.wakeAll();
    m_mutex.unlock();
}

void ServerEmulatorTest::onPrintToConsoleCalled(const QString &msg)
{
    QCOMPARE(m_console_expected_strings.current(), msg);
    m_console_expected_strings.succedOne();
}

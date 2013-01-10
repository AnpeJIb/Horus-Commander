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
    m_emulator.configure("127.0.0.1", "20001", "events.log");
    m_emulator.start();

    m_mutex.lock();
    m_condition.wait(&m_mutex);
    m_mutex.unlock();

    QCOMPARE(m_emulator.exitResult(), ServerEmulator::UNDEFINED);
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

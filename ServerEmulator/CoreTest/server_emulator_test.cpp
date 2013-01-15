#include "server_emulator_test.h"

#include <QtTest/QtTest>

ServerEmulatorTest::ServerEmulatorTest(QObject *parent) :
    QObject(parent)
{
    m_file_path = "events.log";
}

void ServerEmulatorTest::initTestCase()
{
    m_reader.configure(m_file_path);

    connect(&m_emulator, SIGNAL(startSuccess()),
            this, SLOT(onStartSuccess()), Qt::DirectConnection);
    connect(&m_emulator, SIGNAL(printToConsoleCalled(QString)),
            this, SLOT(onPrintToConsoleCalled(const QString&)), Qt::DirectConnection);
    connect(&m_reader, SIGNAL(lineRead(QString)),
            this, SLOT(onFileLineRead(QString)), Qt::DirectConnection);

    m_file_expected_strings.reset();
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
    m_emulator.configure("99.88.77.66", "10", m_file_path);
    m_emulator.start();
    m_emulator.wait();

    QCOMPARE(ServerEmulator::START_FAILED, m_emulator.exitResult());
}

void ServerEmulatorTest::testStartSuccess()
{
    m_console_expected_strings.resetIndex();

    m_emulator.configure("127.0.0.1", "20001", m_file_path);
    m_emulator.start();

    m_mutex.lock();
    m_condition.wait(&m_mutex);
    m_mutex.unlock();

    QCOMPARE(ServerEmulator::UNDEFINED, m_emulator.exitResult());
    QVERIFY(m_console_expected_strings.areAllSucceded());
}

void ServerEmulatorTest::testUser1Joined()
{
    QString callsign = "TestPilot1";
    QString ip_addr = "192.168.1.10";

    m_console_expected_strings.reset();
    m_console_expected_strings.append(QString("socket channel '1' start creating: ip %1:20001").arg(ip_addr));
    m_console_expected_strings.append(QString("Chat: --- %1 joins the game.").arg(callsign));
    m_console_expected_strings.append(
                QString("socket channel '1', ip %1:20001, %2, is complete created.").arg(ip_addr, callsign));

    m_emulator.userJoined(callsign, ip_addr);

    QVERIFY(m_console_expected_strings.areAllSucceded());
}

void ServerEmulatorTest::testUser2Joined()
{
    QString callsign = "TestPilot2";
    QString ip_addr = "192.168.1.11";

    m_console_expected_strings.reset();
    m_console_expected_strings.append(QString("socket channel '3' start creating: ip %1:20001").arg(ip_addr));
    m_console_expected_strings.append(QString("Chat: --- %1 joins the game.").arg(callsign));
    m_console_expected_strings.append(
                QString("socket channel '3', ip %1:20001, %2, is complete created.").arg(ip_addr, callsign));

    m_emulator.userJoined(callsign, ip_addr);

    QVERIFY(m_console_expected_strings.areAllSucceded());
}

void ServerEmulatorTest::cleanupTestCase()
{
    m_emulator.stop();
    m_emulator.wait();

    m_reader.requestStop();
    m_reader.wait();

    QCOMPARE(ServerEmulator::STOPPED_NORMALLY, m_emulator.exitResult());
}

void ServerEmulatorTest::onStartSuccess()
{
    m_mutex.lock();
    m_condition.wakeAll();
    m_mutex.unlock();
}

void ServerEmulatorTest::onPrintToConsoleCalled(const QString &msg)
{
    QCOMPARE(msg, m_console_expected_strings.current());
    m_console_expected_strings.succedOne();
}

void ServerEmulatorTest::onFileLineRead(const QString &line)
{
    QCOMPARE(line, m_file_expected_strings.current());
    m_file_expected_strings.succedOne();
}

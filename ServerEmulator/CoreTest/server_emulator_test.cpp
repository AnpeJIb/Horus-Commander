#include "server_emulator_test.h"

#include <QtTest/QtTest>

ServerEmulatorTest::ServerEmulatorTest(QObject *parent)
    : QObject(parent),
      m_file_path("events.log"),
      m_mission_path("Net/dogfight/test.mis")
{
    /** For timestamps like [8:55:27 PM] */
    QString short_format = "^\\[\\d{1,2}:\\d{2}:\\d{2} [A|P]M\\] (.+)";

    /** For timestamps like [Jan 17, 2013 8:55:27 PM] */
    QString long_format = short_format;
    long_format.insert(3, "\\w{3} \\d{1,2}, \\d{4} ");

    m_re_short_time_log_line.setPattern(short_format);
    m_re_long_time_log_line.setPattern(long_format);
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
    m_console_expected_strings.append("1>");
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

    m_reader.start();
}

void ServerEmulatorTest::testPilot1Joined()
{
    testPilotJoined("TestPilot1", "192.168.1.10", "1");
}

void ServerEmulatorTest::testPilot2Joined()
{
    testPilotJoined("TestPilot2", "192.168.1.11", "3");
}

void ServerEmulatorTest::testPilot1Left()
{
    testPilotLeft("TestPilot1", "192.168.1.10", "1");
}

void ServerEmulatorTest::testPilot2Left()
{
    testPilotLeft("TestPilot2", "192.168.1.11", "3");
}

void ServerEmulatorTest::testMissionLoad()
{
    m_console_expected_strings.reset();
    m_console_expected_strings.append("Mission NOT loaded");
    m_console_expected_strings.append("2>");

    m_console_expected_strings.append(QString("Loading mission %1...").arg(m_mission_path));
    m_console_expected_strings.append("Load bridges");
    m_console_expected_strings.append("Load static objects");
    m_console_expected_strings.append("##### House without collision (3do/Tree/Tree2.sim)");
    m_console_expected_strings.append("##### House without collision (3do/Buildings/Port/Floor/live.sim)");
    m_console_expected_strings.append("##### House without collision (3do/Buildings/Port/BaseSegment/live.sim)");
    m_console_expected_strings.append(QString("Mission: %1 is Loaded").arg(m_mission_path));
    m_console_expected_strings.append("3>");
    m_console_expected_strings.append(QString("Mission: %1 is Loaded").arg(m_mission_path));
    m_console_expected_strings.append("4>");

    m_emulator.processExternalInput("mission");
    m_emulator.processExternalInput(QString("mission LOAD %1").arg(m_mission_path));
    m_emulator.processExternalInput("mission");

    QVERIFY(m_console_expected_strings.areAllSucceded());
}

void ServerEmulatorTest::testMissionBegin()
{
    m_console_expected_strings.reset();
    m_console_expected_strings.append(QString("Mission: %1 is Loaded").arg(m_mission_path));
    m_console_expected_strings.append("5>");
    m_console_expected_strings.append(QString("Mission: %1 is Playing").arg(m_mission_path));
    m_console_expected_strings.append("6>");
    m_console_expected_strings.append(QString("Mission: %1 is Playing").arg(m_mission_path));
    m_console_expected_strings.append("7>");

    m_file_expected_strings.reset();
    m_file_expected_strings.append(QString("l:Mission: %1 is Playing").arg(m_mission_path));
    m_file_expected_strings.append("s:Mission BEGIN");

    m_emulator.processExternalInput("mission");
    m_emulator.processExternalInput("mission BEGIN");
    m_emulator.processExternalInput("mission");

    m_sleep_cond.wait(&m_sleep_mx, 1000);

    QVERIFY(m_console_expected_strings.areAllSucceded());
    QVERIFY(m_file_expected_strings.areAllSucceded());
}

void ServerEmulatorTest::testMissionEnd()
{
    m_console_expected_strings.reset();
    m_console_expected_strings.append(QString("Mission: %1 is Playing").arg(m_mission_path));
    m_console_expected_strings.append("8>");
    m_console_expected_strings.append("9>");
    m_console_expected_strings.append(QString("Mission: %1 is Loaded").arg(m_mission_path));
    m_console_expected_strings.append("10>");

    m_file_expected_strings.reset();
    m_file_expected_strings.append("s:Mission END");

    m_emulator.processExternalInput("mission");
    m_emulator.processExternalInput("mission END");
    m_emulator.processExternalInput("mission");

    m_sleep_cond.wait(&m_sleep_mx, 1000);

    QVERIFY(m_console_expected_strings.areAllSucceded());
    QVERIFY(m_file_expected_strings.areAllSucceded());
}

void ServerEmulatorTest::testMissionUnload()
{
    m_console_expected_strings.reset();
    m_console_expected_strings.append(QString("Mission: %1 is Loaded").arg(m_mission_path));
    m_console_expected_strings.append("11>");
    m_console_expected_strings.append("12>");
    m_console_expected_strings.append("Mission NOT loaded");
    m_console_expected_strings.append("13>");

    m_emulator.processExternalInput("mission");
    m_emulator.processExternalInput("mission DESTROY");
    m_emulator.processExternalInput("mission");

    QVERIFY(m_console_expected_strings.areAllSucceded());
}

void ServerEmulatorTest::testServerInfo()
{
    m_console_expected_strings.reset();

    m_console_expected_strings.append("Type: Local server");
    m_console_expected_strings.append("Name: Server emulator");
    m_console_expected_strings.append("Description: Emulated IL-2 FB server with limited features" \
                                      "for IL-2 Horus Team purposes");
    m_console_expected_strings.append("14>");

    m_emulator.processExternalInput("server");

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

void ServerEmulatorTest::testPilotJoined(
        const QString &callsign, const QString &ip_addr, const QString &channel_number)
{
    m_console_expected_strings.reset();

    m_console_expected_strings.append(QString("socket channel '%1' start creating: ip %2:20001").arg(
        channel_number, ip_addr));
    m_console_expected_strings.append(QString("Chat: --- %1 joins the game.").arg(callsign));
    m_console_expected_strings.append(QString("socket channel '%1', ip %2:20001, %3, is complete created.").arg(
        channel_number, ip_addr, callsign));

    m_emulator.pilotJoined(callsign, ip_addr);

    QVERIFY(m_console_expected_strings.areAllSucceded());
}

void ServerEmulatorTest::testPilotLeft(const QString &callsign, const QString &ip_addr, const QString &channel_number)
{
    m_console_expected_strings.reset();
    m_console_expected_strings.append(QString("socketConnection with %1:20001 on channel %2 lost.  " \
                                      "Reason: Remote user has left the game.").arg(
                                          ip_addr,
                                          channel_number));
    m_console_expected_strings.append(QString("Chat: --- %1 has left the game.").arg(callsign));

    m_emulator.pilotLeft(callsign);

    QVERIFY(m_console_expected_strings.areAllSucceded());
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
    QString expected = m_file_expected_strings.current();
    bool short_date = expected.startsWith("s");
    expected = expected.remove(0, 2);

    QString incoming;

    if (short_date && m_re_short_time_log_line.exactMatch(line))
    {
        incoming = m_re_short_time_log_line.cap(1);
    } else if ((short_date==false) && m_re_long_time_log_line.exactMatch(line))
    {
        incoming = m_re_long_time_log_line.cap(1);
    } else {
        QFAIL("Wrong date format");
    }

    QCOMPARE(incoming, expected);
    m_file_expected_strings.succedOne();
}

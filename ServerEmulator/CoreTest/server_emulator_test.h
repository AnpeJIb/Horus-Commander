#ifndef SERVER_EMULATOR_TEST_H
#define SERVER_EMULATOR_TEST_H

#include <QObject>
#include <QString>
#include <QWaitCondition>
#include <QMutex>

#include "server_emulator.h"
#include "expected_strings.h"
#include "file_line_reader.h"

class ServerEmulatorTest : public QObject
{
    Q_OBJECT
public:
    explicit ServerEmulatorTest(QObject *parent = 0);

public slots:
    void onStartSuccess();
    void onPrintToConsoleCalled(const QString& msg);
    void onFileLineRead(const QString& line);
    
private slots:
    void initTestCase();
    void testStartFail();
    void testStartSuccess();

    void testPilot1Joined();
    void testPilot2Joined();

    void testPilot1Left();
    void testPilot2Left();

    void cleanupTestCase();

private:
    void testPilotJoined(const QString& callsign, const QString& ip_addr, const QString& channel_number);
    void testPilotLeft(const QString& callsign, const QString& ip_addr, const QString& channel_number);

    ServerEmulator m_emulator;
    FileLineReader m_reader;

    QWaitCondition m_condition;
    QMutex m_mutex;

    ExpectedStrings m_console_expected_strings;
    ExpectedStrings m_file_expected_strings;

    QString m_file_path;
};

#endif // SERVER_EMULATOR_TEST_H

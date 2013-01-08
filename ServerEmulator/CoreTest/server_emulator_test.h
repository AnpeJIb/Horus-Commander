#ifndef SERVER_EMULATOR_TEST_H
#define SERVER_EMULATOR_TEST_H

#include <QObject>

#include "server_emulator.h"

class ServerEmulatorTest : public QObject
{
    Q_OBJECT
public:
    explicit ServerEmulatorTest(QObject *parent = 0);
    
private slots:

private:
    ServerEmulator emulator;
};

#endif // SERVER_EMULATOR_TEST_H

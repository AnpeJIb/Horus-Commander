#ifndef SERVER_EMULATOR_H
#define SERVER_EMULATOR_H

#include "stream_server.h"

class ServerEmulator
{
public:
    ServerEmulator();

private:
    StreamServer::pointer server;
};

#endif // SERVER_EMULATOR_H

#ifndef GSCONSOLE_H
#define GSCONSOLE_H

#include "file.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifdef _WIN32_
    #include <winsock2.h>
    #include "winsock_helper.h"
#elif _UNIX_
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <errno.h>
#endif

class GsConsole
{
public:
    GsConsole();

    bool init();
    void clearUp();

    void console_line_rd(char* line, int size, int offset, RL_STAT* stat);
    void console_line_wr(char* line, int size);

    int socketDescriptor(){return m_socketFD;}

private:
    bool socketMakeNonblocking();
    void socketAddrPrepare(struct sockaddr_in* addr);

#ifdef _WIN32_
    SOCKET m_socketFD;
#elif _UNIX_
    int waitRX(int fd);
    int waitTX(int fd);

    int m_socketFD;
#endif

    struct timeval m_waitd;
    fd_set m_flagsRD, m_flagsWR;
};

#endif // GSCONSOLE_H

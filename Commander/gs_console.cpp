#include "gs_console.h"
#include "status_print.h"
#include "config.h"

#include <QObject>

GsConsole::GsConsole()
{
#ifdef _WIN32_
    m_socketFD = INVALID_SOCKET;
#elif _UNIX_
    m_socketFD = 0;
#endif
    m_connected = false;
}

void GsConsole::init()
{
    STATUS_PRINT::NEW(QObject::tr("Initializing console socket"));

    m_connected = true;

    while (1)
    {
#ifdef _WIN32_
        Sleep(2000);

        WSADATA wsadata;
        if (WSAStartup(MAKEWORD(2, 2), &wsadata))
        {
            m_connected = false;
            break;
        }
#elif _UNIX_
        sleep(2);
#endif

#ifdef _WIN32_
        m_socketFD = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
        if (m_socketFD == INVALID_SOCKET)
#elif _UNIX_
        m_socketFD = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socketFD < 0)
#endif
        {
            STATUS_PRINT::ERROR_(QObject::tr("Socket not created"));
            m_connected = false;
            break;
        }

        struct sockaddr_in addr;
        socketAddrPrepare(&addr);
        socketMakeNonblocking();

#ifdef _WIN32_
        if ((WSAConnect(m_socketFD, (struct sockaddr*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
                && (WSAGetLastError() != WSAEWOULDBLOCK))
#elif _UNIX_
        if ((connect(m_socketFD, (struct sockaddr*)&addr, sizeof(addr)) < 0) && (errno != EINPROGRESS))
#endif
        {
            STATUS_PRINT::ERROR_(QObject::tr("Connection failed"));
            m_connected = false;
            break;
        }

        m_waitd.tv_sec = 2;
        m_waitd.tv_usec = 0;

        FD_ZERO(&m_flagsRD);
        FD_ZERO(&m_flagsWR);

        FD_SET(m_socketFD, &m_flagsRD);
        FD_SET(m_socketFD, &m_flagsWR);

        int res = select(m_socketFD+1, &m_flagsRD, &m_flagsWR, (fd_set*)0, &m_waitd);

#ifdef _WIN32_
        if (res  == SOCKET_ERROR)
#elif _UNIX_
        if (res < 0)
#endif
        {
            STATUS_PRINT::ERROR_(QObject::tr("Select failed"));
            m_connected = false;
        }

        break;
    }

    if	(m_connected)
        STATUS_PRINT::DONE();
    else
        STATUS_PRINT::FAIL();
}

void GsConsole::startParsing()
{
    if (m_connected)
        m_parser.start();
}

void GsConsole::clearUp()
{
    if (m_socketFD == 0) return;

    STATUS_PRINT::NEW(QObject::tr("Closing console socket"));

    m_parser.stop();
    m_parser.wait();

#ifdef _WIN32_
    closesocket(m_socketFD);
    WSACleanup();
    m_socketFD = INVALID_SOCKET;
#elif _UNIX_
    close(m_socketFD);
    m_socketFD = 0;
#endif
    m_connected = false;

    STATUS_PRINT::DONE();
}

bool GsConsole::socketMakeNonblocking()
{
#ifdef _WIN32_
    DWORD num_bytes;
    WSAOVERLAPPED overlapped;
    u_long iMode=1;

    if (WSAIoctl(m_socketFD, FIONBIO, &iMode, sizeof(iMode), NULL, 0, &num_bytes, &overlapped, NULL) == SOCKET_ERROR)
    {
        STATUS_PRINT::ERROR_(QObject::tr("Cannot make non-blocking"));
        return false;
    }
    Sleep(1000);
#elif  _UNIX_
    int flags = fcntl(m_socketFD, F_GETFL, 0);
    fcntl(m_socketFD, F_SETFL, flags | O_NONBLOCK);
    sleep(1);
#endif

    return true;
}

void GsConsole::socketAddrPrepare(sockaddr_in *addr)
{
    (*addr).sin_family 		= AF_INET;
    (*addr).sin_addr.s_addr = inet_addr(CONFIG::NET.localIP().toStdString().c_str());

    int portNo = CONFIG::NET.localPort();

#ifdef _WIN32_
    if (WSAHtons(m_socketFD, (u_short)portNo, &((*addr).sin_port)) == SOCKET_ERROR)
        STATUS_PRINT::ERROR_(QObject::tr("WSAHtons call failed"));
#elif  _UNIX_
    (*addr).sin_port = htons(portNo);
#endif
}

void GsConsole::console_line_rd(char *line, int size, int offset, RL_STAT *stat)
{
#ifdef _WIN32_
    sock_line_rd(m_socketFD, line, size, offset, stat);
#elif  _UNIX_
    if (waitRX(m_socketFD) < 0) return;
    line_rd(m_socketFD, line, size, offset, stat);
#endif
}

void GsConsole::console_line_wr(const char *line, int size)
{
#ifdef _WIN32_
    sock_line_wr(m_socketFD, line, size);
#elif  _UNIX_
    waitTX(m_socketFD);
    line_wr(m_socketFD, line, size);
#endif
}

#ifdef _UNIX_
int GsConsole::waitRX(int fd)
{
    FD_ZERO(&m_flagsRD);
    FD_SET(fd, &m_flagsRD);
    int result = select(fd+1, &m_flagsRD, NULL, NULL, NULL );
    if ( result <= 0 ) return result;
    if ( FD_ISSET(fd, &m_flagsRD) ) return 1;
    return 0;
}

int GsConsole::waitTX(int fd)
{
    FD_ZERO(&m_flagsWR);
    FD_SET(fd, &m_flagsWR);
    int result = select(fd+1, NULL, &m_flagsWR, NULL, NULL );
    if ( result <= 0 ) return result;
    if ( FD_ISSET(fd, &m_flagsWR) ) return 1;
    return 0;
}
#endif

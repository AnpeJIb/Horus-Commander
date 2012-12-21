#include "gs_command.h"
#include "config.h"
#include "str.h"
#include "sc.h"
#include "status_print.h"

#ifdef _WIN32_
    #include <windows.h>
#elif _UNIX_
    #include <unistd.h>
#endif

QString GsCommands::get_GC()
{
    return "GC";
}

QString GsCommands::get_RUN_FILE(QString relativePath)
{
    return QString("f ").append(relativePath);
}

QString GsCommands::get_TIMEOUT(int secondsDelay, QString cmd)
{
    return QString("timeout ").append(QString::number(secondsDelay)).append(" ").append(cmd);
}

QString GsCommands::get_EXIT()
{
    return "exit";
}

void GsCommands::init()
{
    m_greetingFormat = tr("Hello, %1! ")
            .append(QString(tr("Welcome to '%1' server!")).arg(CONFIG::GENERAL.serverName()));
    m_aboutCommander = tr("Server is under Horus Commander control "
                          "(v.%1, www.il2-horus-system.wikia.com).").arg(APP_VERSION);
    m_kickingAll = tr("Kicking all!");
}

void GsCommands::exit()
{
    cmdSend(GsCommands::get_EXIT().toUtf8().constData());
}

void GsCommands::chatAll(const char* msg)
{
    chat(msg, CHAT_ADDRESSEE_ALL);
}

void GsCommands::chatCallsign(const char* callsign, const char* msg)
{
    int callsignLen = strlen(callsign);
    char ecallsign[callsignLen*6-5];
    STR::escapeUnicode((char*)callsign, callsignLen, ecallsign, sizeof ecallsign);

    // 3 is for "TO "
    char addressee[strlen(ecallsign)+3];
    sprintf(addressee, CHAT_ADDRESSEE_CALLSIGN, ecallsign);

    chat(msg, addressee);
}

void GsCommands::chatUsernum(int num, const char* msg)
{
    chat(msg, QString(CHAT_ADDRESSEE_USERNUM).append(QString::number(num)).toStdString().c_str());
}

void GsCommands::chatArmy(quint8 armyNum, const char* msg)
{
    chat(msg, QString(CHAT_ADDRESSEE_ARMY).append(armyNum).toStdString().c_str());
}

void GsCommands::chat(const char* msg, const char* addressee)
{
    int eLen = GS_CMD_CHAT_MAX_LEN*6;
    char emsg[eLen];

    // 9 is for "chat \"", "\" ", '\0'
    char cmd[eLen+strlen(addressee)+9];

    char chunk[GS_CMD_CHAT_MAX_LEN*2];

    int offset = 0;
    int end = strlen(msg);

    while (offset<end)
    {
        memset(chunk, '\0', sizeof chunk);
        offset = STR::copySymbols((char*)msg, end, GS_CMD_CHAT_MAX_LEN, offset, (char*)&chunk, sizeof chunk);

        STR::escapeUnicode(chunk, strlen(chunk), emsg, sizeof emsg);
        sprintf(cmd, GS_CMD_CHAT, emsg, addressee);

        cmdSend((const char*)&cmd);
    }
}

void GsCommands::kickAll()
{
    STATUS_PRINT::NEW(m_kickingAll);

    for(quint8 i=0; i<3; i++)
    {
        chatAll(m_kickingAll.toUtf8().constData());

#ifdef _WIN32_
        Sleep(2000);
#elif _UNIX_
        sleep(2);
#endif
    }

    const char* cmd = GS_CMD_KICK_FIRST;

    for(quint8 i=0; i< CONFIG::NET.channelsCount(); i++)
        cmdSend(cmd);

    STATUS_PRINT::DONE();
}

void GsCommands::cmdSend(const char* cmd)
{
    m_txMx.lock();

    SC::CONSOLE.console_line_wr(cmd, strlen(cmd));

    #ifdef _WIN32_
        Sleep(10);
    #elif _UNIX_
        usleep(10*1000);
    #endif

    m_txMx.unlock();
}

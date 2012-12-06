#include "server_process.h"
#include "server_commander.h"
#include "gs_config.h"
#include "gs_scripts.h"
#include "gs_path.h"
#include "config.h"
#include "status_print.h"
#include "file.h"

#include <signal.h>
#include <QFile>

static bool m_loaded;

ServerProcess::ServerProcess(QObject *parent)
    :   QThread(parent),
        m_doRun(false)
{
}

void ServerProcess::run()
{
    if (isServerRunning())
    {
        STATUS_PRINT::WARN_(tr("Server is already running"));
        return;
    }

    STATUS_PRINT::DEBUG_(tr("Starting server"));

    if (checkRootPath()==false)
    {
        STATUS_PRINT::FAIL();
        return;
    }

    m_doRun          = true;
    m_launchedBefore = false;

    forever
    {
        m_loaded = false;

        checkLaunchedBefore();
        if (m_doRun==false) break;

        if (prepare()==false)
        {
            m_doRun=false;
            break;
        }

        if (processCreate() == false)
        {
            onProcessStop();
            continue;
        }

        onProcessStart();

        STATUS_PRINT::ERROR_(tr("Game server is shut down"));

        if (m_doRun==false) break;
    }
}

bool ServerProcess::checkRootPath()
{
    STATUS_PRINT::NEW(tr("Checking root path"));

    QString path = SC::GS::PATH::exePath();
    QFile file(path);

    bool exists = file.exists();

    if (exists)
    {
        STATUS_PRINT::DONE();
    } else {
        STATUS_PRINT::ERROR_(tr("Could not find server's executable at path \"%1\"").arg(path));
        STATUS_PRINT::FAIL();
    }

    file.close();

    return exists;
}

void ServerProcess::checkLaunchedBefore()
{
    if (m_launchedBefore)
    {
        for(int i=10; i>0; i--)
        {
            if (m_doRun==false) break;

            STATUS_PRINT::INFO_(tr("Restarting server in...%1").arg(i));
            sleep(1);
        }
    }
}

bool ServerProcess::prepare()
{
    if (SC::GS::CFG::init()         == false) return false;
    if (SC::GS::SCRIPTS::generate() == false) return false;

#ifdef _WIN32_
    m_hChildStd_OUT_Rd = NULL;
    m_hChildStd_OUT_Wr = NULL;
#elif _UNIX_
    m_PID = (pid_t) 0;
#endif

    return true;
}

#ifdef _UNIX_
static void* processCreateRaw(void *)
{
    pid_t pid = fork();

    if (pid==0)
    {
        QString cmd = QString("wine ").append(SC::GS::PATH::exePath())
                .append(">").append(SC::GS::PATH::stdOutPath())
                .append(" 2>").append(SC::GS::PATH::stdErrPath());

        execl("/bin/sh", "sh", "-c", cmd.toStdString().c_str(), (char*) 0);
        _exit(127);
    }

    int childExitStatus;
    waitpid(pid, &childExitStatus, 0);

    return NULL;
}
#endif

bool ServerProcess::processCreate()
{
    STATUS_PRINT::NEW(tr("Creating game server process"));

#ifdef _WIN32_
    SECURITY_ATTRIBUTES sec;
    sec.nLength = sizeof(SECURITY_ATTRIBUTES);
    sec.bInheritHandle = TRUE;
    sec.lpSecurityDescriptor = NULL;

    if ( ! CreatePipe(&m_hChildStd_OUT_Rd, &m_hChildStd_OUT_Wr, &sec, 0) )
    {
        STATUS_PRINT::ERROR_(tr("Cannot create StdoutRd pipe"));
        STATUS_PRINT::FAIL();
        return false;
    }

    if ( ! SetHandleInformation(m_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
    {
        STATUS_PRINT::ERROR_(tr("Cannot set Stdout HandleInformation"));
        STATUS_PRINT::FAIL();
        return false;
    }

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdError = NULL;
    si.hStdOutput = m_hChildStd_OUT_Wr;
    si.hStdInput = NULL;
    si.dwFlags |= STARTF_USESTDHANDLES;

    ZeroMemory(&m_PINF, sizeof(m_PINF));

    QString cmd = QString("cmd /c ").append(SC::GS::PATH::exePath());

    if( CreateProcess(
                NULL,
                (WCHAR*)cmd.toStdWString().c_str(),
                NULL,
                NULL,
                TRUE,
                0,
                NULL,
                NULL,
                &si,
                &m_PINF) == 0)
    {
        STATUS_PRINT::FAIL();
        return FALSE;
    }

    childWaitLoaded();
#elif _UNIX_

    m_PID = fork();

    if (m_PID < 0)
    {
        STATUS_PRINT::ERROR_(tr("Failed to fork"));
        STATUS_PRINT::FAIL();
        return false;
    } else if (m_PID == 0) {
        signal(SIGINT,	SIG_IGN);
        signal(SIGTERM,	SIG_IGN);
        signal(SIGABRT,	SIG_IGN);

        pthread_t thrd;
        pthread_create(&thrd, NULL, &processCreateRaw, NULL);
        childWaitLoaded();
        pthread_join(thrd, NULL);
        _exit(127);
    }
#endif

    STATUS_PRINT::DONE();
    return true;
}


void ServerProcess::childWaitLoaded()
{
#ifdef _WIN32_
    Sleep(2000);
#elif _UNIX_
    sleep(2);
#endif

    int line_len = 64;
    char line[line_len];
    int offset = 0;
    RL_STAT stat;

#ifdef _UNIX_
    int o_flags = O_RDONLY | O_NONBLOCK;
    int stream = open(SC::GS::PATH::stdOutPath().toStdString().c_str(), o_flags);
#endif

    while(1)
    {
    #ifdef _WIN32_
        hnd_line_rd(m_hChildStd_OUT_Rd, line, line_len, offset, &stat);
    #elif _UNIX_
        line_rd(stream, line, line_len, offset, &stat);
    #endif

        if (stat.finished == FALSE)
        {
            offset += stat.length;

        #ifdef _WIN32_
            Sleep(500);
        #elif _UNIX_
            usleep(500*1000);
        #endif

        } else {
            offset = 0;
            if (strstr(line, "1>") != NULL)
            {
                suppressStdout();

            #ifdef _WIN32_
                setLoaded();
            #elif _UNIX_
                kill(getppid(), SIGUSR1);
            #endif

                break;
            }
        }
    }

#ifdef _UNIX_
    close(stream);
    QFile::remove(SC::GS::PATH::stdOutPath());
#endif
}

void ServerProcess::suppressStdout()
{
#ifdef _WIN32_
    CloseHandle(m_hChildStd_OUT_Rd);
    CloseHandle(m_hChildStd_OUT_Wr);
#elif _UNIX_
    int newOut = open(DEV_NULL, O_WRONLY);
    dup2(newOut, STDOUT_FILENO);
    close(newOut);
#endif
}

void ServerProcess::onProcessStop()
{
    // TODO:
    m_launchedBefore = true;
}


void ServerProcess::onProcessStart()
{
    parentWaitLoaded();

    if (isServerRunning() && SC::CONSOLE.init())
    {
        // TODO:
        processWait();
    } else {
        processKill();
    }
    onProcessStop();
}

void ServerProcess::parentWaitLoaded()
{
    STATUS_PRINT::NEW(tr("Waiting for server is loaded"));

    int tries = 30;
    while ((m_loaded == false) && m_doRun)
    {
        sleep(1);

        tries--;
        if (tries == 0)
        {
            STATUS_PRINT::ERROR_(tr("Game server loading timeout"));
            break;
        }
    }

    if (m_loaded)
        STATUS_PRINT::DONE();
    else
        STATUS_PRINT::FAIL();
}

void ServerProcess::processWait()
{
#ifdef _WIN32_
    WaitForSingleObject(m_PINF.hProcess, INFINITE);
    CloseHandle(m_PINF.hProcess);
    CloseHandle(m_PINF.hThread);
#elif _UNIX_
    int childExitStatus;
    waitpid(m_PID, &childExitStatus, 0);
    m_PID = (pid_t) 0;
#endif
    STATUS_PRINT::INFO_(tr("Game server's process finished"));
}

void ServerProcess::processKill()
{
#ifdef _WIN32_
    DWORD dwExitCode = 0;
    GetExitCodeProcess(m_PINF.hProcess, &dwExitCode);
    TerminateProcess(m_PINF.hProcess, dwExitCode);
#elif _UNIX_
    kill(m_PID, SIGKILL);
#endif
}

void ServerProcess::stop()
{
    m_doRun = false;
    SC::MSSN.stop();
    // TODO:
}

#ifdef _WIN32_
void ServerProcess::setLoaded()
{
    m_loaded = true;
}
#elif _UNIX_
void setLoaded(int sig)
{
    Q_UNUSED(sig)
    m_loaded = true;
}

void ServerProcess::setHook_SIGUSR()
{
    signal(SIGUSR1, setLoaded);
}
#endif

bool ServerProcess::isServerRunning()
{
    return m_doRun && m_loaded;
}

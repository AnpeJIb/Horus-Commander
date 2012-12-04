#include "serverprocess.h"
#include "servercommander.h"
#include "gsconfig.h"
#include "gsscripts.h"
#include "config.h"
#include "statusprint.h"

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
    if (isRunning())
    {
        STATUS_PRINT::WARN(tr("Server is already running"));
        return;
    }

    STATUS_PRINT::DEBUG(tr("Starting server"));

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

        STATUS_PRINT::ERROR(tr("Game server is shut down"));

        if (m_doRun==false) break;
    }
}

bool ServerProcess::checkRootPath()
{
    STATUS_PRINT::NEW(tr("Checking root path"));

    QString path = CONFIG::GENERAL.serverPath() + PATH_SEP + SERVER_EXE;
    QFile file(path);

    bool exists = file.exists();

    if (exists)
    {
        STATUS_PRINT::DONE();
    } else {
        STATUS_PRINT::ERROR(tr("Could not find server's executable at path \"%1\"").arg(path));
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

            STATUS_PRINT::INFO(tr("Restarting server in...%1").arg(i));
            sleep(1);
        }
    }
}

bool ServerProcess::prepare()
{
    if (SC::GS::CFG::init()         == false) return false;
    if (SC::GS::SCRIPTS::generate() == false) return false;
    return true;
}

bool ServerProcess::processCreate()
{
    // TODO:
    return false;
}

void ServerProcess::onProcessStart()
{
    waitLoaded();

    if (isRunning() && SC::CONSOLE.init())
    {
        // TODO:
        processWait();
    } else {
        kill();
    }
    onProcessStop();
}

void ServerProcess::waitLoaded()
{
    STATUS_PRINT::NEW(tr("Waiting for server is loaded"));

    int tries = 30;
    while ((m_loaded == false) && m_doRun)
    {
        sleep(1);

        tries--;
        if (tries == 0)
        {
            STATUS_PRINT::ERROR(tr("Game server loading timeout"));
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
    // TODO:
}

void ServerProcess::onProcessStop()
{
    // TODO:
    m_launchedBefore = true;
}

void ServerProcess::kill()
{
    // TODO:
}

void ServerProcess::stop()
{
    SC::MSSN.stop();
    // TODO:
}

#ifdef _UNIX_
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

#ifdef _WIN32_
void ServerProcess::setLoaded()
{
    m_loaded = true;
}
#endif

bool ServerProcess::isRunning()
{
    return m_doRun && m_loaded;
}

#ifndef SERVERPROCESS_H
#define SERVERPROCESS_H

#include <QThread>
#include "fileext.h"

#ifdef _WIN32_
    #include <windows.h>
    #include "winproc.h"
#elif _UNIX_
    #include <sys/wait.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <pthread.h>
    #include <time.h>
#endif

class ServerProcess : public QThread
{
    Q_OBJECT
public:
    explicit ServerProcess(QObject *parent = 0);

#ifdef _WIN32_
    void setLoaded();
#elif _UNIX_
    void setHook_SIGUSR();
#endif

    bool isServerRunning();
    void stop();

protected:
    void run();

private:
    bool checkRootPath();
    void checkLaunchedBefore();
    bool prepare();
    bool processCreate();
    void childWaitLoaded();
    void suppressStdout();
    void onProcessStop();
    void onProcessStart();
    void parentWaitLoaded();
    void processWait();
    void processKill();

#ifdef _WIN32_
    PROCESS_INFORMATION m_PINF;
    HANDLE m_hChildStd_OUT_Rd;
    HANDLE m_hChildStd_OUT_Wr;
#elif _UNIX_
    pid_t m_PID;
#endif

    bool m_doRun;
    bool m_launchedBefore;
};

#endif // SERVERPROCESS_H

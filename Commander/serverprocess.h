#ifndef SERVERPROCESS_H
#define SERVERPROCESS_H

#include <QThread>

#include "fileext.h"

#define SERVER_EXE  "il2server" FILE_EXT_EXE

class ServerProcess : public QThread
{
    Q_OBJECT
public:
    explicit ServerProcess(QObject *parent = 0);

#ifdef _UNIX_
    void setHook_SIGUSR();
#endif

#ifdef _WIN32_
    void setLoaded();
#endif

    bool isRunning();
    void stop();

protected:
    void run();

private:
    bool checkRootPath();
    void checkLaunchedBefore();

    bool prepare();
    bool processCreate();
    void onProcessStart();
    void waitLoaded();
    void processWait();
    void onProcessStop();

    void kill();

    bool m_doRun;
    bool m_launchedBefore;
};

#endif // SERVERPROCESS_H

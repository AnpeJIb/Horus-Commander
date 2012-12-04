#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QLibraryInfo>

#include <signal.h>

#include "config.h"
#include "logs.h"
#include "servercommander.h"

void parseArgs(int argc, char *argv[]);
void initSignalHooks();
void terminationHandler(int sig);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LOGS::INIT();
    CONFIG::INIT();

    CONFIG::LOAD();
    LOGS::UPDATE_FILE_LOGGER();

    /** Init language */
    QString lCode = CONFIG::GENERAL.langCode();

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + lCode, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load(QString("l10n/").append(lCode));
    a.installTranslator(&myappTranslator);

    initSignalHooks();

    /** Check commandline arguments */
    parseArgs(argc, argv);

    if (CONFIG::GENERAL.isDaemonMode())
    {
        // TODO: start work here
        return 0;
    }

    /** Check system tray */
    if (QSystemTrayIcon::isSystemTrayAvailable()==false)
    {
        QMessageBox::critical(
                    0,
                    QObject::tr("Systray"),
                    QObject::tr("I couldn't detect any system tray on this system."));
        exit(EXIT_FAILURE);
    }
    QApplication::setQuitOnLastWindowClosed(false);

    /** Show main window */
    MainWindow w;
    Q_UNUSED(w)

    return a.exec();
}

void parseArgs(int argc, char *argv[])
{
    for (int i=1; i<argc; i++)
        if (QString(argv[i])== "-d")
            CONFIG::GENERAL.setDaemonMode(true);
}

void initSignalHooks()
{
    STATUS_PRINT::DEBUG(QObject::tr("Setting signal hooks"));

#ifdef _UNIX_
    SC::SP.setHook_SIGUSR();
    signal(SIGPIPE,	SIG_IGN);
#endif

    signal(SIGINT,	terminationHandler);
    signal(SIGTERM,	terminationHandler);
    signal(SIGABRT,	terminationHandler);
}

void terminationHandler(int sig)
{
    STATUS_PRINT::DEBUG(QObject::tr("Termination signal received"));

    Q_UNUSED(sig)
    SC::SP.stop();
}

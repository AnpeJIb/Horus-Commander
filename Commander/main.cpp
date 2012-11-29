#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include "config.h"
#include "logs.h"

void parseArgs(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /** Init LOGS */
    static LOGS logs;
    Q_UNUSED(logs)

    /** Init CONFIG */
    static CONFIG cfg;
    Q_UNUSED(cfg)

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

    parseArgs(argc, argv);

    if (CONFIG::GENERAL.isDaemonMode())
    {
        // TODO: start work here
        return 0;
    }

    MainWindow w;
    w.show();
    return a.exec();
}

void parseArgs(int argc, char *argv[])
{
    for (int i=1; i<argc; i++)
        if (QString(argv[i])== "-d")
            CONFIG::GENERAL.setDaemonMode(true);
}

#include "main_window.h"

#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QLibraryInfo>

#include "system_path.h"
#include "primary_config_service.h"
#include "general_config_service.h"
#include "log_config_service.h"
#include "log_service.h"
#include "file_logger.h"

FileLogger* fileLogger = NULL;

using namespace Service::ConfigService;

void init();
void initLog();
void initLanguage();
void updateLog();
void checkSystemTray();
void cleanUp();
void cleanUpLogger();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(APP_VERSION);

    init();

    // TODO: check deamon mode

    checkSystemTray();
    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;
    Q_UNUSED(w)

    int result = a.exec();
    cleanUp();
    return result;
}

void init()
{
    initLog();

    PrimaryConfigService::init(
                Path::System::config(),
                Path::System::dataSource());

    updateLog();
    initLanguage();
}

void initLog()
{
    fileLogger = new FileLogger(Path::System::log());
    fileLogger->setLevel(Config::Log::LEVEL_ALL);
    Service::LOGGER::registerLogger(fileLogger);
}

void updateLog()
{
    Service::ConfigService::LogConfigService service;
    fileLogger->setLevel(service.logLevel(fileLogger->logKind()));
}

void initLanguage()
{
    GeneralConfigService service;

    QString lCode = service.languageCode();

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + lCode, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load(QString("l10n/").append(lCode));
    qApp->installTranslator(&myappTranslator);
}

void checkSystemTray()
{
    if (QSystemTrayIcon::isSystemTrayAvailable()==false)
    {
        QMessageBox::critical(
                    0,
                    QObject::tr("Systray"),
                    QObject::tr("I couldn't detect any system tray on this system."));
        exit(EXIT_FAILURE);
    }
}

void cleanUp()
{
    cleanUpLogger();
    PrimaryConfigService::cleanUp();
}

void cleanUpLogger()
{
    Service::LOGGER::unregisterLogger(fileLogger);
    delete fileLogger;
}

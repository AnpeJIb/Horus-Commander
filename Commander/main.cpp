#include "main_window.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include "primary_config_service.h"
#include "general_config_service.h"
#include "system_path.h"

using namespace Service::ConfigService;

void init();
void initLanguage();
void cleanUp();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(APP_VERSION);

    init();

    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;
    Q_UNUSED(w)

    int result = a.exec();

    cleanUp();

    return result;
}

void init()
{
    PrimaryConfigService::init(
                Path::System::config(),
                Path::System::dataSource());

    initLanguage();
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

void cleanUp()
{
    PrimaryConfigService::cleanUp();
}

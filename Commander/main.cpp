#include "main_window.h"

#include <QApplication>

#include "primary_config_service.h"
#include "system_path.h"

using namespace Config;

void init();
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
}

void cleanUp()
{
    PrimaryConfigService::cleanUp();
}

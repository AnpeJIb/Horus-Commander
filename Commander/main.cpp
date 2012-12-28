#include "main_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(APP_VERSION);

    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;
    Q_UNUSED(w)

    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /** Init CONFIG */
    static CONFIG cfg;
    Q_UNUSED(cfg)

    CONFIG::LOAD();

    /** Init language */
    QString lCode = CONFIG::GENERAL.langCode();

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + lCode, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load(QString("l10n/").append(lCode));
    a.installTranslator(&myappTranslator);

    MainWindow w;
    w.show();
    
    return a.exec();
}

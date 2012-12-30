#include "general_config.h"

#include <QObject>
#include <QDir>

namespace Config { namespace General {

QList<SupportedLanguage> m_supportedLanguages;
QList<SupportedDB> m_supportedDBs;

void populateSupportedLanguages()
{
    SupportedLanguage en;
    en.codeName = "en";
    en.title = QObject::tr("English");
    en.icon = QIcon(":/img/langEn.png");

    SupportedLanguage ru;
    ru.codeName = "ru";
    ru.title = QObject::tr("Russian");
    ru.icon = QIcon(":/img/langRu.png");

    m_supportedLanguages << en;
    m_supportedLanguages << ru;
}

void populateSupportedDatabases()
{
    SupportedDB SQLite;
    SQLite.kind  = DB_SQLITE;
    SQLite.title = "SQLite";

    m_supportedDBs << SQLite;
}

QList<SupportedLanguage>& supportedLanguages()
{
    if (m_supportedLanguages.isEmpty())
        populateSupportedLanguages();

    return m_supportedLanguages;
}

QList<SupportedDB>& supportedDatabases()
{
    if (m_supportedDBs.isEmpty())
        populateSupportedDatabases();

    return m_supportedDBs;
}

SupportedLanguage& defaultLanguage()
{
    return supportedLanguages().first();
}

SupportedDB& defaultDB()
{
    return supportedDatabases().first();
}

QString defaultServerPath()
{
    return QDir::currentPath();
}

}}

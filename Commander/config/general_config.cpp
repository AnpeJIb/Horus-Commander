#include "general_config.h"

#include <QObject>
#include <QDir>

namespace Config { namespace General {

QList<AvailableLanguage> m_availableLanguages;

void populateAvailableLanguages()
{
    AvailableLanguage en;
    en.codeName = "en";
    en.title = QObject::tr("English");
    en.icon = QIcon(":/img/langEn.png");

    AvailableLanguage ru;
    ru.codeName = "ru";
    ru.title = QObject::tr("Russian");
    ru.icon = QIcon(":/img/langRu.png");

    m_availableLanguages << en;
    m_availableLanguages << ru;
}

QList<AvailableLanguage> &availableLanguages()
{
    if (m_availableLanguages.isEmpty())
        populateAvailableLanguages();

    return m_availableLanguages;
}

QString& defaultLanguageCode()
{
    return availableLanguages().first().codeName;
}

QString defaultServerPath()
{
    return QDir::currentPath();
}

}}

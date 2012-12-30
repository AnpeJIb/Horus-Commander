#ifndef GENERAL_CONFIG_H
#define GENERAL_CONFIG_H

#include <QString>
#include <QList>
#include <QMap>
#include <QIcon>

#include "title_carrier.h"
#include "code_name_carrier.h"

using namespace Domain;

namespace Config { namespace General {

enum DB_TYPE
{
    DB_SQLITE = 0
};

class AvailableLanguage: public TitleCarrier, public CodeNameCarrier
{
public:
    QIcon icon;
};

typedef struct
{
    QString serverPath;
    QString langCode;
    QMap<DB_TYPE, QString> connectionStrings;
} GeneralConfig;

QList<AvailableLanguage>& availableLanguages();

QString& defaultLanguageCode();
QString defaultServerPath();

}}

#endif // GENERAL_CONFIG_H

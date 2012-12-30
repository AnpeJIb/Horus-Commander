#ifndef GENERAL_CONFIG_H
#define GENERAL_CONFIG_H

#include <QString>
#include <QList>
#include <QMap>
#include <QIcon>

#include "title_carrier.h"
#include "kind_carrier.h"
#include "code_name_carrier.h"

using namespace Domain;

namespace Config { namespace General {

enum DB_KIND
{
    DB_NONE   = 0,
    DB_SQLITE = 1
};

typedef struct
{
    QString path;
} SQLiteConfig;

class SupportedLanguage: public TitleCarrier, public CodeNameCarrier
{
public:
    QIcon icon;
};

class SupportedDB: public TitleCarrier, public KindCarrier
{
};

QList<SupportedLanguage>& supportedLanguages();
QList<SupportedDB>& supportedDatabases();

SupportedLanguage& defaultLanguage();
SupportedDB& defaultDB();
QString defaultServerPath();

}}

#endif // GENERAL_CONFIG_H

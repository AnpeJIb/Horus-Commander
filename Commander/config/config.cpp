#include "config.h"
#include "fileext.h"
#include "statusprint.h"

#include <QFile>
#include <QTextStream>

#define XML_ROOT  "horusConfig"

static QString CONFIG_PATH = XML_ROOT FILE_EXT_XML;

GeneralConfig CONFIG::GENERAL;
QList<ConfigModule*> CONFIG::CHILDREN;


CONFIG::CONFIG()
{
    CONFIG::CHILDREN << &(CONFIG::GENERAL);
}

void CONFIG::SAVE()
{
    QFile file(CONFIG_PATH);

    if(file.open(QIODevice::WriteOnly) == false)
    {
        QString str = QObject::tr("Could not open config file \"%1\" for writing");
        str.arg(CONFIG_PATH);
        STATUS_PRINT::ERROR(str);

        return;
    }

    QDomDocument CONFIG_DOC;

    QDomProcessingInstruction pi =
            CONFIG_DOC.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    CONFIG_DOC.insertBefore(pi, QDomNode());

    QDomElement root = CONFIG_DOC.createElement(XML_ROOT);
    CONFIG_DOC.appendChild(root);

    foreach (ConfigModule* ch, CONFIG::CHILDREN)
        ch->save(&root, &CONFIG_DOC);

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    ts << CONFIG_DOC.toString();
    file.close();
}

void CONFIG::LOAD()
{
    QFile file(CONFIG_PATH);

    if(file.open(QIODevice::ReadWrite) == false)
    {
        QString str = QObject::tr("Could not open config file \"%1\" for reading");
        str.arg(CONFIG_PATH);
        STATUS_PRINT::ERROR(str);

        return;
    }

    QDomDocument CONFIG_DOC;

    if(CONFIG_DOC.setContent(&file) == false)
    {
        STATUS_PRINT::DEBUG(QObject::tr("Bad config file"));
        file.close();
        CONFIG::DEFAULTS();
        CONFIG::SAVE();
        return;
    }

    file.close();

    QDomElement root = CONFIG_DOC.documentElement();

    if(root.tagName() != XML_ROOT)
    {
        STATUS_PRINT::ERROR(QObject::tr("Wrong config root"));
        return;
    }

    QDomNode n;
    for(n = root.firstChild();
        n.isNull()==false;
        n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if(e.isNull()) continue;

        foreach (ConfigModule* ch, CONFIG::CHILDREN)
            ch->load(&e);
    }
}

void CONFIG::DEFAULTS()
{
    foreach (ConfigModule* ch, CONFIG::CHILDREN)
        ch->loadDefaults();
}

bool CONFIG::IS_CHANGED()
{
    bool result = false;

    foreach (ConfigModule* ch, CONFIG::CHILDREN)
        result |= ch->isChanged();

    return result;
}

QString CONFIG::PATH()
{
    return CONFIG_PATH;
}

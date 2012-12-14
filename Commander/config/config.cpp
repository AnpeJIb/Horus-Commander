#include "config.h"
#include "file_ext.h"
#include "status_print.h"

#include <QFile>
#include <QDir>
#include <QTextStream>

#define XML_ROOT  "horusConfig"

static QString m_CONFIG_DIR_PATH = QDir::homePath().append(PATH_SEP).append(".horusCommander");
static QString CONFIG_NAME = QString("config").append(FILE_EXT_XML);
static QString m_CONFIG_PATH = QString(m_CONFIG_DIR_PATH).append(PATH_SEP).append(CONFIG_NAME);

GeneralConfig   CONFIG::GENERAL;
LogConfig       CONFIG::LOG;
NetConfig       CONFIG::NET;
WindowConfig    CONFIG::WINDOW;

static QList<ConfigModule*> CHILDREN;

void CONFIG::INIT()
{
    QDir d;
    if (d.exists(m_CONFIG_DIR_PATH)==false)
        d.mkpath(m_CONFIG_DIR_PATH);

    CHILDREN << &(CONFIG::GENERAL);
    CHILDREN << &(CONFIG::LOG);
    CHILDREN << &(CONFIG::NET);
    CHILDREN << &(CONFIG::WINDOW);
}

void CONFIG::SAVE()
{
    QFile file(m_CONFIG_PATH);

    if(file.open(QIODevice::WriteOnly) == false)
    {
        QString str = QObject::tr("Could not open config file \"%1\" for writing");
        str.arg(m_CONFIG_PATH);
        STATUS_PRINT::ERROR_(str);

        return;
    }

    QDomDocument CONFIG_DOC;

    QDomProcessingInstruction pi =
            CONFIG_DOC.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    CONFIG_DOC.insertBefore(pi, QDomNode());

    QDomElement root = CONFIG_DOC.createElement(XML_ROOT);
    CONFIG_DOC.appendChild(root);

    foreach (ConfigModule* ch, CHILDREN)
        ch->save(&root, &CONFIG_DOC);

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    ts << CONFIG_DOC.toString();
    file.close();
}

void CONFIG::LOAD()
{
    QFile file(m_CONFIG_PATH);

    if(file.open(QIODevice::ReadWrite) == false)
    {
        QString str = QObject::tr("Could not open config file \"%1\" for reading");
        str.arg(m_CONFIG_PATH);
        STATUS_PRINT::ERROR_(str);

        return;
    }

    QDomDocument CONFIG_DOC;

    if(CONFIG_DOC.setContent(&file) == false)
    {
        STATUS_PRINT::DEBUG_(QObject::tr("Bad config file"));
        file.close();
        CONFIG::DEFAULTS();
        CONFIG::SAVE();
        return;
    }

    file.close();

    QDomElement root = CONFIG_DOC.documentElement();

    if(root.tagName() != XML_ROOT)
    {
        STATUS_PRINT::ERROR_(QObject::tr("Wrong config root"));
        return;
    }

    QDomNode n;
    for(n = root.firstChild();
        n.isNull()==false;
        n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if(e.isNull()) continue;

        foreach (ConfigModule* ch, CHILDREN)
            ch->load(&e);
    }
}

void CONFIG::DEFAULTS()
{
    foreach (ConfigModule* ch, CHILDREN)
        ch->loadDefaults();
}

bool CONFIG::IS_CHANGED()
{
    bool result = false;

    foreach (ConfigModule* ch, CHILDREN)
        result |= ch->isChanged();

    return result;
}

QString CONFIG::DIR_PATH()
{
    return m_CONFIG_DIR_PATH;
}

QString CONFIG::FILE_PATH()
{
    return m_CONFIG_PATH;
}

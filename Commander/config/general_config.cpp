#include "general_config.h"
#include "status_print.h"

#define XML_ELEM            "general"
#define LANG_ELEM           "lang"
#define DAEMON_MODE_ELEM    "daemonMode"
#define SERVER_ELEM         "server"
#define SERVER_PATH_ELEM    "path"
#define SERVER_NAME_ELEM    "name"
#define SERVER_DESCR_ELEM   "description"

GeneralConfig::GeneralConfig()
{
}

void GeneralConfig::save(QDomElement *root, QDomDocument* doc)
{
    QDomElement elem = doc->createElement(XML_ELEM);

    saveLangCode(&elem, doc);
    saveDaemonMode(&elem, doc);
    saveServer(&elem, doc);

    root->appendChild(elem);
    notChanged();
}

void GeneralConfig::saveLangCode(QDomElement *root, QDomDocument *doc)
{
    QDomElement elem = doc->createElement(LANG_ELEM);
    root->appendChild(elem);

    QDomText t = doc->createTextNode(m_langCode);
    elem.appendChild(t);
}

void GeneralConfig::saveDaemonMode(QDomElement *root, QDomDocument *doc)
{
    QDomElement elem = doc->createElement(DAEMON_MODE_ELEM);
    root->appendChild(elem);

    QDomText t = doc->createTextNode(QString::number(m_daemonMode));
    elem.appendChild(t);
}

void GeneralConfig::saveServer(QDomElement *root, QDomDocument *doc)
{
    QDomElement elem = doc->createElement(SERVER_ELEM);
    root->appendChild(elem);

    /** Save Server path */
    QDomElement path = doc->createElement(SERVER_PATH_ELEM);
    elem.appendChild(path);

    QDomText pathValue = doc->createTextNode(m_serverPath);
    path.appendChild(pathValue);

    /** Save Server name */
    QDomElement name = doc->createElement(SERVER_NAME_ELEM);
    elem.appendChild(name);

    QDomText nameValue = doc->createTextNode(m_serverName);
    name.appendChild(nameValue);

    /** Save Server name */
    QDomElement descr = doc->createElement(SERVER_DESCR_ELEM);
    elem.appendChild(descr);

    QDomText descrValue = doc->createTextNode(m_serverDescr);
    descr.appendChild(descrValue);
}

void GeneralConfig::load(QDomElement *root)
{
    if(root->tagName() != XML_ELEM) return;

    QDomNode n;
    for(n = root->firstChild();
        n.isNull()==false;
        n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if(e.isNull()) continue;

        if (loadLangCode(&e)) continue;
        if (loadDaemonMode(&e)) continue;
        loadServer(&e);
    }

    notChanged();
}

bool GeneralConfig::loadLangCode(QDomElement *root)
{
    if(root->tagName() != LANG_ELEM) return false;
    setLangCode(root->text());
    return true;
}

bool GeneralConfig::loadDaemonMode(QDomElement *root)
{
    if(root->tagName() != DAEMON_MODE_ELEM) return false;
    setDaemonMode(root->text().toInt()>0);
    return true;
}

bool GeneralConfig::loadServer(QDomElement *root)
{
    if(root->tagName() != SERVER_ELEM) return false;

    QDomNode n;
    for(n = root->firstChild();
        n.isNull()==false;
        n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if(e.isNull()) continue;

        if (e.tagName()==SERVER_PATH_ELEM)
            setServerPath(e.text());
        else if (e.tagName()==SERVER_NAME_ELEM)
            setServerName(e.text());
        if (e.tagName()==SERVER_DESCR_ELEM)
            setServerDescr(e.text());
    }

    return true;
}

void GeneralConfig::loadDefaults()
{
    setLangCode(    DEFAULT_LANG_CODE);
    setDaemonMode(  DEFAULT_DEAMON_MODE);
    setServerPath(  DEFAULT_SERVER_PATH);
    setServerName(  DEFAULT_SERVER_NAME);
    setServerDescr( DEFAULT_SERVER_DESCR);
}

void GeneralConfig::setLangCode(QString value)
{
    if (value.isNull() || value.isEmpty()) return;

    if (m_langCode!=value)
    {
        m_langCode = value;
        changed();
    }
}
QString GeneralConfig::langCode() const {return m_langCode;}

void GeneralConfig::setDaemonMode(bool value)
{
    if (m_daemonMode != value)
    {
        m_daemonMode = value;
        changed();
    }
}
bool GeneralConfig::isDaemonMode() {return m_daemonMode;}

void GeneralConfig::setServerPath(QString value)
{
    if (m_serverPath!=value)
    {
        m_serverPath = value;
        changed();
    }
}
QString GeneralConfig::serverPath(){return m_serverPath;}

void GeneralConfig::setServerName(QString value)
{
    if (m_serverName!=value)
    {
        m_serverName = value;
        changed();
    }
}
QString GeneralConfig::serverName(){return m_serverName;}

void GeneralConfig::setServerDescr(QString value)
{
    if (m_serverDescr!=value)
    {
        m_serverDescr = value;
        changed();
    }
}
QString GeneralConfig::serverDescr(){return m_serverDescr;}

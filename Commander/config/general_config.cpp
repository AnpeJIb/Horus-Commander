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

    appendTextNode(&elem, doc, LANG_ELEM,           m_langCode);
    appendTextNode(&elem, doc, DAEMON_MODE_ELEM,    QString::number(m_daemonMode));
    saveServer(&elem, doc);

    root->appendChild(elem);
    notChanged();
}

void GeneralConfig::saveServer(QDomElement *root, QDomDocument *doc)
{
    QDomElement elem = doc->createElement(SERVER_ELEM);
    root->appendChild(elem);

    appendTextNode(&elem, doc, SERVER_PATH_ELEM,    m_serverPath);
    appendTextNode(&elem, doc, SERVER_NAME_ELEM,    m_serverName);
    appendTextNode(&elem, doc, SERVER_DESCR_ELEM,   m_serverDescr);
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

        if (e.tagName() == LANG_ELEM)
            {setLangCode(e.text());             continue;}
        if (e.tagName() == DAEMON_MODE_ELEM)
            {setDaemonMode(e.text().toInt()>0); continue;}
        loadServer(&e);
    }

    notChanged();
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
            {setServerPath(e.text());    continue;}
        if (e.tagName()==SERVER_NAME_ELEM)
            {setServerName(e.text());    continue;}
        if (e.tagName()==SERVER_DESCR_ELEM)
            {setServerDescr(e.text());   continue;}
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

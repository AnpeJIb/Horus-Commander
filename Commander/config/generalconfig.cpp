#include "generalconfig.h"
#include "statusprint.h"

#define XML_ELEM            "general"
#define LANG_ELEM           "lang"
#define DAEMON_MODE_ELEM    "daemonMode"

#define DEFAULT_LANG_CODE       "en"
#define DEFAULT_DEAMON_MODE     false

GeneralConfig::GeneralConfig()
{
}

void GeneralConfig::save(QDomElement *root, QDomDocument* doc)
{
    QDomElement elem = doc->createElement(XML_ELEM);

    saveLangCode(&elem, doc);
    saveDaemonMode(&elem, doc);

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
        loadDaemonMode(&e);
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

void GeneralConfig::loadDefaults()
{
    setLangCode(    DEFAULT_LANG_CODE);
    setDaemonMode(  DEFAULT_DEAMON_MODE);
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

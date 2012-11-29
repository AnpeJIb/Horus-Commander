#include "generalconfig.h"
#include "statusprint.h"

#define XML_ELEM    "general"
#define LANG_ELEM   "lang"

#define DEFAULT_LANG_CODE "en"

GeneralConfig::GeneralConfig()
{
}

void GeneralConfig::save(QDomElement *root, QDomDocument* doc)
{
    QDomElement elem = doc->createElement(XML_ELEM);
    saveLangCode(&elem, doc);
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

        loadLangCode(&e);
    }

    notChanged();
}

void GeneralConfig::loadLangCode(QDomElement *root)
{
    if(root->tagName() != LANG_ELEM) return;
    setLangCode(root->text());
}

void GeneralConfig::loadDefaults()
{
    setLangCode(DEFAULT_LANG_CODE);
}

void GeneralConfig::setLangCode(QString value)
{
    if (value.isNull() || value.isEmpty()) return;
    m_langCode = value;

    changed();
}

QString GeneralConfig::langCode() const {return m_langCode;}

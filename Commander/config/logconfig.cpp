#include "logconfig.h"

#define XML_ELEM "log"

LogConfig::LogConfig()
{
    addChild((m_FILE  = new CommonLogConfig("file")));
    addChild((m_GUI   = new CommonLogConfig("gui")));
}

void LogConfig::save(QDomElement *root, QDomDocument *doc)
{
    QDomElement elem = doc->createElement(XML_ELEM);

    saveChildren(&elem, doc);
    root->appendChild(elem);
    notChanged();
}

void LogConfig::load(QDomElement *root)
{
    if(root->tagName() != XML_ELEM) return;

    QDomNode n;
    for(n = root->firstChild();
        n.isNull()==false;
        n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if(e.isNull()) continue;

        loadChildren(&e);
    }

    notChanged();
}

void LogConfig::loadDefaults() {loadChildrenDefaults();}

CommonLogConfig *LogConfig::FILE() {return m_FILE;}
CommonLogConfig *LogConfig::GUI()  {return m_GUI;}

#include "commonlogconfig.h"
#include "statusprint.h"

#define DEFAULT_ENABLE  true
#define DEFAULT_LEVEL   StatusPrinter::LEVEL_ALL

#define XML_ATTR_ENABLE "enable"
#define XML_ATTR_LEVEL  "level"

CommonLogConfig::CommonLogConfig(const QString &XML_ELEM)
    : m_XML_ELEM(XML_ELEM)
{
}

void CommonLogConfig::save(QDomElement *root, QDomDocument *doc)
{
    QDomElement elem = doc->createElement(m_XML_ELEM);

    elem.setAttribute(XML_ATTR_ENABLE,  QString::number(m_enable));
    elem.setAttribute(XML_ATTR_LEVEL,  QString::number(m_level));

    root->appendChild(elem);
    notChanged();
}

void CommonLogConfig::load(QDomElement *root)
{
    if(root->tagName() != m_XML_ELEM) return;
    setEnable(root->attribute(XML_ATTR_ENABLE, QString::number(DEFAULT_ENABLE)).toInt()>0);
    setLevel(root->attribute(XML_ATTR_LEVEL, QString::number(DEFAULT_LEVEL)).toInt());
    notChanged();
}

void CommonLogConfig::loadDefaults()
{
    setEnable(DEFAULT_ENABLE);
    setLevel(DEFAULT_LEVEL);
}

bool CommonLogConfig::isEnable() {return m_enable;}
quint8 CommonLogConfig::level(){return m_level;}


void CommonLogConfig::setEnable(bool value)
{
    if (m_enable != value)
    {
        m_enable = value;
        changed();
    }
}

void CommonLogConfig::setLevel(quint8 value)
{
    if (m_level != value)
    {
        m_level = value;
        changed();
    }
}

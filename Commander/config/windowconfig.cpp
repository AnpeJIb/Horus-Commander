#include "windowconfig.h"

#define XML_ELEM            "window"
#define GEOM_ELEM       "geometry"

#define XML_ATTR_MINIMIZED  "isMinimized"
#define XML_ATTR_X          "x"
#define XML_ATTR_Y          "y"
#define XML_ATTR_W          "w"
#define XML_ATTR_H          "h"

#define DEFAULT_GEOM_X  -1
#define DEFAULT_GEOM_Y  -1
#define DEFAULT_GEOM_W  300
#define DEFAULT_GEOM_H  200

#define DEFAULT_MINIMIZED false

WindowConfig::WindowConfig()
{
}

void WindowConfig::save(QDomElement *root, QDomDocument *doc)
{
    QDomElement elem = doc->createElement(XML_ELEM);

    saveGeometry(&elem, doc);
    saveMinimized(&elem);

    root->appendChild(elem);
    notChanged();
}

void WindowConfig::saveGeometry(QDomElement *root, QDomDocument *doc)
{
    QDomElement elem = doc->createElement(GEOM_ELEM);
    root->appendChild(elem);

    elem.setAttribute(XML_ATTR_X,  QString::number(m_geometry.x()));
    elem.setAttribute(XML_ATTR_Y,  QString::number(m_geometry.y()));
    elem.setAttribute(XML_ATTR_W,  QString::number(m_geometry.width()));
    elem.setAttribute(XML_ATTR_H,  QString::number(m_geometry.height()));
}

void WindowConfig::saveMinimized(QDomElement *root)
{
    root->setAttribute(XML_ATTR_MINIMIZED,  QString::number(m_minimized));
}

void WindowConfig::load(QDomElement *root)
{
    if(root->tagName() != XML_ELEM) return;

    loadMinimized(root);

    QDomNode n;
    for(n = root->firstChild();
        n.isNull()==false;
        n = n.nextSibling())
    {
        QDomElement e = n.toElement();
        if(e.isNull()) continue;

        if (loadGeometry(&e)) continue;
    }

    notChanged();
}

bool WindowConfig::loadGeometry(QDomElement *root)
{
    if(root->tagName() != GEOM_ELEM) return false;

    QRect geom;

    geom.setX(root->attribute(      XML_ATTR_X, QString::number(DEFAULT_GEOM_X)).toInt());
    geom.setY(root->attribute(      XML_ATTR_Y, QString::number(DEFAULT_GEOM_Y)).toInt());
    geom.setWidth(root->attribute(  XML_ATTR_W, QString::number(DEFAULT_GEOM_W)).toInt());
    geom.setHeight(root->attribute( XML_ATTR_H, QString::number(DEFAULT_GEOM_H)).toInt());

    setGeometry(geom);

    return true;
}

void WindowConfig::loadMinimized(QDomElement *root)
{
    setMinimized(root->attribute(XML_ATTR_MINIMIZED, QString::number(DEFAULT_MINIMIZED)).toInt()>0);
}

void WindowConfig::loadDefaults()
{
    QRect geom;
    geom.setRect(DEFAULT_GEOM_X, DEFAULT_GEOM_X,
                 DEFAULT_GEOM_W, DEFAULT_GEOM_H);
    setGeometry(geom);
    setMinimized(DEFAULT_MINIMIZED);
}

void WindowConfig::setGeometry(const QRect &value)
{
    if ((m_geometry.x()       != value.x())
    ||  (m_geometry.y()       != value.y())
    ||  (m_geometry.height()  != value.height())
    ||  (m_geometry.width()   != value.width()))
    {
        m_geometry = value;
        changed();
    }
}
QRect WindowConfig::geometry() const {return m_geometry;}

void WindowConfig::setMinimized(bool value)
{
    if (m_minimized != value)
    {
        m_minimized = value;
        changed();
    }
}
bool WindowConfig::isMinimized() {return m_minimized;}

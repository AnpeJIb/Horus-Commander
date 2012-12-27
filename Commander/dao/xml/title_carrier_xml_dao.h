#ifndef TITLE_CARRIER_XML_DAO_H
#define TITLE_CARRIER_XML_DAO_H

#include <QObject>
#include <QDomElement>
#include "title_carrier.h"

#define XML_ATTR_TITLE "title"

class TitleCarrierXmlDao
{
public:
    static domain_title_t titleFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_TITLE, QObject::tr("No title"));
    }

    static void titleToXmlElement(const domain_title_t& title, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_TITLE, title);
    }

    static bool isTitleSuitable(const void* title, const QDomElement &element)
    {
        return (*(domain_title_t*)(title)) == titleFromXmlElement(element);
    }
};

#endif // TITLE_CARRIER_XML_DAO_H

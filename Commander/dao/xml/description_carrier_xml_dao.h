#ifndef DESCRIPTION_CARRIER_XML_DAO_H
#define DESCRIPTION_CARRIER_XML_DAO_H

#include <QObject>
#include <QDomElement>
#include "description_carrier.h"

#define XML_ATTR_DESCR "description"

class DescriptionCarrierXmlDao
{
public:
    static domain_descr_t descriptionFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_DESCR, QObject::tr("No description"));
    }

    static void descriptionToXmlElement(const domain_descr_t& descr, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_DESCR, descr);
    }

    static bool isDescriptionSuitable(const void* descr, const QDomElement &element)
    {
        return (*(domain_descr_t*)(descr)) == descriptionFromXmlElement(element);
    }
};

#endif // DESCRIPTION_CARRIER_XML_DAO_H

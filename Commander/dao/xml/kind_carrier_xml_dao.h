#ifndef KIND_CARRIER_XML_DAO_H
#define KIND_CARRIER_XML_DAO_H

#include <QDomElement>
#include "kind_carrier.h"

#define XML_ATTR_KIND "kind"

class KindCarrierXmlDao
{
public:
    static domain_kind_t kindFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_KIND, "0").toInt();
    }

    static void kindToXmlElement(domain_kind_t kind, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_KIND, QString::number(kind));
    }

    static bool isKindSuitable(const void* kind, const QDomElement &element)
    {
        return (*(domain_kind_t*)(kind)) == kindFromXmlElement(element);
    }
};

#endif // KIND_CARRIER_XML_DAO_H

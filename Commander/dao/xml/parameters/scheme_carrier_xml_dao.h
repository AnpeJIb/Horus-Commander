#ifndef SCHEME_CARRIER_XML_DAO_H
#define SCHEME_CARRIER_XML_DAO_H

#include <QDomElement>
#include "generic_domain.h"

#define XML_ATTR_SCHEME_ID "scheme_id"

class SchemeCarrierXmlDao
{
public:
    static domain_id_t schemeIdFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_SCHEME_ID, "0").toULongLong();
    }

    static void schemeIdToXmlElement(domain_id_t id, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_SCHEME_ID, QString::number(id));
    }

    static bool isSchemeIdSuitable(const void* id, const QDomElement &element)
    {
        return (*(domain_id_t*)(id)) == schemeIdFromXmlElement(element);
    }
};

#endif // SCHEME_CARRIER_XML_DAO_H

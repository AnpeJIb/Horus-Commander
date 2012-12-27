#ifndef PARENT_CARRIER_XML_DAO_H
#define PARENT_CARRIER_XML_DAO_H

#include <QDomElement>
#include "generic_domain.h"

#define XML_ATTR_PARENT_ID "parent_id"

class ParentCarrierXmlDao
{
public:
    static domain_id_t parentIdFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_PARENT_ID, "0").toULongLong();
    }

    static void parentIdToXmlElement(domain_id_t id, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_PARENT_ID, QString::number(id));
    }

    static bool isParentIdSuitable(const void* id, const QDomElement &element)
    {
        return (*(domain_id_t*)(id)) == parentIdFromXmlElement(element);
    }
};

#endif // PARENT_CARRIER_XML_DAO_H

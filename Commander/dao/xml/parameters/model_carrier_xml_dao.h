#ifndef MODEL_CARRIER_XML_DAO_H
#define MODEL_CARRIER_XML_DAO_H

#include <QDomElement>
#include "generic_domain.h"

#define XML_ATTR_MODEL_ID "model_id"

class ModelCarrierXmlDao
{
public:
    static domain_id_t modelIdFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_MODEL_ID, "0").toULongLong();
    }

    static void modelIdToXmlElement(domain_id_t id, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_MODEL_ID, QString::number(id));
    }

    static bool isModelIdSuitable(const void* id, const QDomElement &element)
    {
        return (*(domain_id_t*)(id)) == modelIdFromXmlElement(element);
    }
};

#endif // MODEL_CARRIER_XML_DAO_H

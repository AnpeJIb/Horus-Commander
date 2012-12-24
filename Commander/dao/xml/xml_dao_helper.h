#ifndef XML_DAO_HELPER_H
#define XML_DAO_HELPER_H

#include <QDomElement>
#include "generic_domain.h"

#define XML_ATTR_ID        "id"
#define XML_ATTR_TITLE     "title"
#define XML_ATTR_KIND      "kind"
#define XML_ATTR_CODE_NAME "codeName"
#define XML_ATTR_PARENT_ID "parent_id"
#define XML_ATTR_MODEL_ID  "model_id"
#define XML_ATTR_SIMPLE_PARAMETER_ID "simple_parameter_id"

inline domain_id_t idFromXmlElement(const QDomElement& element)
{
    return element.attribute(XML_ATTR_ID, "0").toULongLong();
}

inline void idToXmlElement(domain_id_t id, QDomElement* element)
{
    element->setAttribute(XML_ATTR_ID, QString::number(id));
}

#endif // XML_DAO_HELPER_H

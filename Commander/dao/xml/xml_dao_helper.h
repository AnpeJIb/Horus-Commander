#ifndef XML_DAO_HELPER_H
#define XML_DAO_HELPER_H

#include <QDomElement>
#include "generic_domain.h"
#include "title_carrier.h"
#include "kind_carrier.h"

#define XML_ATTR_ID        "id"
#define XML_ATTR_TITLE     "title"
#define XML_ATTR_KIND      "kind"
#define XML_ATTR_CODE_NAME "codeName"
#define XML_ATTR_PARENT_ID "parent_id"
#define XML_ATTR_MODEL_ID  "model_id"
#define XML_ATTR_SIMPLE_PARAMETER_ID "simple_parameter_id"

/** ID helpers */

inline domain_id_t idFromXmlElement(const QDomElement& element)
{
    return element.attribute(XML_ATTR_ID, "0").toULongLong();
}

inline void idToXmlElement(domain_id_t id, QDomElement* element)
{
    element->setAttribute(XML_ATTR_ID, QString::number(id));
}

/** Title helpers */

inline domain_title_t titleFromXmlElement(const QDomElement& element)
{
    return element.attribute(XML_ATTR_TITLE, "No title");
}

inline void titleToXmlElement(const domain_title_t& title, QDomElement* element)
{
    element->setAttribute(XML_ATTR_TITLE, title);
}

/** Kind helpers */

inline domain_kind_t kindFromXmlElement(const QDomElement& element)
{
    return element.attribute(XML_ATTR_KIND, "0").toInt();
}

inline void kindToXmlElement(domain_kind_t kind, QDomElement* element)
{
    element->setAttribute(XML_ATTR_KIND, QString::number(kind));
}

#endif // XML_DAO_HELPER_H

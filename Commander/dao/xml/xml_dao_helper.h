#ifndef XML_DAO_HELPER_H
#define XML_DAO_HELPER_H

#include <QDomElement>
#include "generic_domain.h"
#include "title_carrier.h"
#include "kind_carrier.h"
#include "code_name_carrier.h"

#define XML_ATTR_ID_DEFAULT "0"

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
    return element.attribute(XML_ATTR_ID, XML_ATTR_ID_DEFAULT).toULongLong();
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
    return element.attribute(XML_ATTR_KIND, XML_ATTR_ID_DEFAULT).toInt();
}

inline void kindToXmlElement(domain_kind_t kind, QDomElement* element)
{
    element->setAttribute(XML_ATTR_KIND, QString::number(kind));
}

/** Code name helpers */

inline domain_codeName_t codeNameFromXmlElement(const QDomElement& element)
{
    return element.attribute(XML_ATTR_CODE_NAME, "NO_CODE_NAME");
}

inline void codeNameToXmlElement(const domain_title_t& codeName, QDomElement* element)
{
    element->setAttribute(XML_ATTR_CODE_NAME, codeName);
}

/** Parent ID helpers */

inline domain_id_t parentIdFromXmlElement(const QDomElement& element)
{
    return element.attribute(XML_ATTR_PARENT_ID, XML_ATTR_ID_DEFAULT).toULongLong();
}

inline void parentIdToXmlElement(domain_id_t id, QDomElement* element)
{
    element->setAttribute(XML_ATTR_PARENT_ID, QString::number(id));
}

/** Model ID helpers */

inline domain_id_t modelIdFromXmlElement(const QDomElement& element)
{
    return element.attribute(XML_ATTR_MODEL_ID, XML_ATTR_ID_DEFAULT).toULongLong();
}

inline void modelIdToXmlElement(domain_id_t id, QDomElement* element)
{
    element->setAttribute(XML_ATTR_MODEL_ID, QString::number(id));
}

/** Simple parameter ID helpers */

inline domain_id_t simpleParameterIdFromXmlElement(const QDomElement& element)
{
    return element.attribute(XML_ATTR_SIMPLE_PARAMETER_ID, XML_ATTR_ID_DEFAULT).toULongLong();
}

inline void simpleParameterIdToXmlElement(domain_id_t id, QDomElement* element)
{
    element->setAttribute(XML_ATTR_SIMPLE_PARAMETER_ID, QString::number(id));
}

#endif // XML_DAO_HELPER_H

#ifndef CODE_NAME_CARRIER_XML_DAO_H
#define CODE_NAME_CARRIER_XML_DAO_H

#include <QDomElement>
#include "code_name_carrier.h"

#define XML_ATTR_CODE_NAME "codeName"

class CodeNameCarrierXmlDao
{
public:
    static domain_codeName_t codeNameFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_CODE_NAME, "NO_CODE_NAME");
    }

    static void codeNameToXmlElement(const domain_codeName_t& codeName, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_CODE_NAME, codeName);
    }

    static bool isCodeNameSuitable(const void* codeName, const QDomElement &element)
    {
        return (*(domain_codeName_t*)(codeName)) == codeNameFromXmlElement(element);
    }
};

#endif // CODE_NAME_CARRIER_XML_DAO_H

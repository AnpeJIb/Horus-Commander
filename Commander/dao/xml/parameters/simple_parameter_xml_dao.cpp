#include "simple_parameter_xml_dao.h"

using namespace Dao::Parameters;

QString SimpleParameterXmlDao::m_tagName = "SimpleParameter";

void SimpleParameterXmlDao::findByTitle(const domain_title_t &title, QList<SimpleParameter *> *result)
{
    findByAttribute((const void*)&title, &isTitleSuitable, result);
}

void SimpleParameterXmlDao::findByCodeName(const domain_codeName_t &codeName, QList<SimpleParameter *> *result)
{
    findByAttribute((const void*)&codeName, &isCodeNameSuitable, result);
}

void SimpleParameterXmlDao::domainToXmlElement(SimpleParameter *domain, QDomElement *element)
{
    idToXmlElement(domain->id, element);
    titleToXmlElement(domain->title, element);
    codeNameToXmlElement(domain->codeName, element);
}

void SimpleParameterXmlDao::domainFromXmlElement(const QDomElement &element, SimpleParameter *domain)
{
    domain->id       = idFromXmlElement(element);
    domain->title    = titleFromXmlElement(element);
    domain->codeName = codeNameFromXmlElement(element);
}

SimpleParameter *SimpleParameterXmlDao::newDomain()
{
    return new SimpleParameter;
}

QDomNode SimpleParameterXmlDao::parentNode(SimpleParameter *domain)
{
    Q_UNUSED(domain)
    return dsDoc.documentElement();
}

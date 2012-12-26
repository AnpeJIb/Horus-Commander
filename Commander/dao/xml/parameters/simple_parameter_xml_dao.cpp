#include "simple_parameter_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

QString SimpleParameterXmlDao::m_tagName = "SimpleParameter";

void SimpleParameterXmlDao::findByTitle(const domain_title_t &title, QList<SimpleParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    domain_title_t tmp_title;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_title = titleFromXmlElement(elem);
        if (tmp_title == title)
            (*result) << cachedOrNewDomain(elem);
    }
}

void SimpleParameterXmlDao::findByCodeName(const domain_codeName_t &codeName, QList<SimpleParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    domain_codeName_t tmp_codeName;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_codeName = codeNameFromXmlElement(elem);

        if (tmp_codeName == codeName)
            (*result) << cachedOrNewDomain(elem);
    }
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

QString SimpleParameterXmlDao::tagName()
{
    return m_tagName;
}

QDomNode SimpleParameterXmlDao::parentNode(SimpleParameter *domain)
{
    Q_UNUSED(domain)
    return dsDoc.documentElement();
}

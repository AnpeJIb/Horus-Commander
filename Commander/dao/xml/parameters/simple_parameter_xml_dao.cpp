#include "simple_parameter_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

QString SimpleParameterXmlDao::m_tagName = "SimpleParameter";

SimpleParameterXmlDao::SimpleParameterXmlDao()
{
}

SimpleParameterXmlDao::~SimpleParameterXmlDao()
{
}

void SimpleParameterXmlDao::save(SimpleParameter *domain)
{
    if (cacheGet(domain->id) != NULL) return;

    domain->id = newId();

    QDomElement root = parentNode(domain).toElement();
    QDomElement elem = dsDoc.createElement(m_tagName);

    domainToXmlElement(domain, &elem);
    root.appendChild(elem);

    cachePut(domain);
}

void SimpleParameterXmlDao::all(QList<SimpleParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    for (int i = 0; i < lst.count(); ++i)
        (*result) << cachedOrNewDomain(lst.at(i).toElement());
}

SimpleParameter *SimpleParameterXmlDao::find(domain_id_t id)
{
    SimpleParameter* result = cacheGet(id);

    if (result != NULL) return result;

    QDomNode node = findXmlNode(id);
    if (node.isNull() == false)
        result = newCachedDomain(node.toElement());

    return result;
}

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

void SimpleParameterXmlDao::update(SimpleParameter *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        QDomElement elem = node.toElement();
        domainToXmlElement(domain, &elem);
    }
}

void SimpleParameterXmlDao::remove(SimpleParameter *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        node.parentNode().removeChild(node);
        cacheRemoveAndDispose(domain->id);
    }
}

SimpleParameter *SimpleParameterXmlDao::cachedOrNewDomain(const QDomElement &element)
{
    domain_id_t id = idFromXmlElement(element);
    SimpleParameter* result = cacheGet(id);

    if (result == NULL)
        result = newCachedDomain(element);

    return result;
}

SimpleParameter *SimpleParameterXmlDao::newCachedDomain(const QDomElement &element)
{
    SimpleParameter* result = new SimpleParameter;

    result->id       = idFromXmlElement(element);
    result->title    = titleFromXmlElement(element);
    result->codeName = codeNameFromXmlElement(element);

    cachePut(result);

    return result;
}

void SimpleParameterXmlDao::domainToXmlElement(SimpleParameter *domain, QDomElement *element)
{
    idToXmlElement(domain->id, element);
    titleToXmlElement(domain->title, element);
    codeNameToXmlElement(domain->codeName, element);
}

QString SimpleParameterXmlDao::tagNameRaw()
{
    return m_tagName;
}

QDomNode SimpleParameterXmlDao::parentNode(SimpleParameter *domain)
{
    Q_UNUSED(domain)
    return dsDoc.documentElement();
}

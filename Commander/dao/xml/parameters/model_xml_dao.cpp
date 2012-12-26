#include "model_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

QString ModelXmlDao::m_tagName = "ParameterModel";

void ModelXmlDao::findByTitle(const domain_title_t& title, QList<Model *> *result)
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

void ModelXmlDao::findByKind(domain_kind_t kind, QList<Model *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    domain_kind_t tmp_kind;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_kind = kindFromXmlElement(elem);

        if (tmp_kind == kind)
            (*result) << cachedOrNewDomain(elem);
    }
}

Model *ModelXmlDao::newDomain()
{
    return new Model;
}

void ModelXmlDao::domainToXmlElement(Model *domain, QDomElement *element)
{
    idToXmlElement(domain->id, element);
    titleToXmlElement(domain->title, element);
    kindToXmlElement(domain->kind, element);
}

void ModelXmlDao::domainFromXmlElement(const QDomElement &element, Model *domain)
{
    domain->id    = idFromXmlElement(element);
    domain->kind  = kindFromXmlElement(element);
    domain->title = titleFromXmlElement(element);
}

QString ModelXmlDao::tagName()
{
    return m_tagName;
}

QDomNode ModelXmlDao::parentNode(Model *domain)
{
    Q_UNUSED(domain)
    return dsDoc.documentElement();
}

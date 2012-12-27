#include "model_xml_dao.h"

using namespace Dao::Parameters;

QString ModelXmlDao::m_tagName = "ParameterModel";

void ModelXmlDao::findByTitle(const domain_title_t& title, QList<Model *> *result)
{
    findByAttribute((const void*)&title, &isTitleSuitable, result);
}

void ModelXmlDao::findByKind(domain_kind_t kind, QList<Model *> *result)
{
    findByAttribute((const void*)&kind, &isKindSuitable, result);
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

QDomNode ModelXmlDao::parentNode(Model *domain)
{
    Q_UNUSED(domain)
    return dsDoc.documentElement();
}

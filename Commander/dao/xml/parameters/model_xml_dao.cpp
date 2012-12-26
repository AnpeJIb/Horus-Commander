#include "model_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

QString ModelXmlDao::m_tagName = "ParameterModel";

ModelXmlDao::ModelXmlDao()
{
}

ModelXmlDao::~ModelXmlDao()
{
}

void ModelXmlDao::save(Model* domain)
{
    if (cacheGet(domain->id) != NULL) return;

    domain->id = newId();

    QDomElement root = parentNode(domain).toElement();
    QDomElement elem = dsDoc.createElement(m_tagName);

    domainToXmlElement(domain, &elem);
    root.appendChild(elem);

    cachePut(domain);
}

void ModelXmlDao::all(QList<Model *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    for (int i = 0; i < lst.count(); ++i)
        (*result) << cachedOrNewDomain(lst.at(i).toElement());
}

Model* ModelXmlDao::find(domain_id_t id)
{
    Model* result = cacheGet(id);

    if (result != NULL) return result;

    QDomNode node = findXmlNode(id);
    if (node.isNull() == false)
        result = newCachedDomain(node.toElement());

    return result;
}

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

void ModelXmlDao::update(Model *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        QDomElement elem = node.toElement();
        domainToXmlElement(domain, &elem);
    }
}

void ModelXmlDao::remove(Model *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        node.parentNode().removeChild(node);
        cacheRemoveAndDispose(domain->id);
    }
}

Model *ModelXmlDao::cachedOrNewDomain(const QDomElement &element)
{
    domain_id_t id = idFromXmlElement(element);
    Model* result = cacheGet(id);

    if (result == NULL)
        result = newCachedDomain(element);

    return result;
}

Model *ModelXmlDao::newCachedDomain(const QDomElement& element)
{
    Model* result = new Model;

    result->id    = idFromXmlElement(element);
    result->kind  = kindFromXmlElement(element);
    result->title = titleFromXmlElement(element);

    cachePut(result);

    return result;
}

void ModelXmlDao::domainToXmlElement(Model *domain, QDomElement *element)
{
    idToXmlElement(domain->id, element);
    titleToXmlElement(domain->title, element);
    kindToXmlElement(domain->kind, element);
}

QString ModelXmlDao::tagNameRaw()
{
    return m_tagName;
}

QDomNode ModelXmlDao::parentNode(Model *domain)
{
    Q_UNUSED(domain)
    return dsDoc.documentElement();
}

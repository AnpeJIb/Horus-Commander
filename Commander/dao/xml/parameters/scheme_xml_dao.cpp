#include "scheme_xml_dao.h"

using namespace Dao::Parameters;

QString SchemeXmlDao::m_tagName = "ParameterScheme";


SchemeXmlDao::SchemeXmlDao()
{
}

SchemeXmlDao::~SchemeXmlDao()
{
}

void SchemeXmlDao::save(Scheme *domain)
{
    /** Check existance in cache */
    if (cache[domain->id] != NULL) return;

    QDomNode root = parentNode(domain);
    if (root.isNull()) return;

    QDomElement elem = dsDoc.createElement(m_tagName);

    domain->id = newId();
    domainToXmlElement(domain, &elem);

    root.appendChild(elem);

    /** Put to cache */
    cache[domain->id] = domain;
}

void SchemeXmlDao::all(QList<Scheme *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    for (int i = 0; i < lst.count(); ++i)
        (*result) << cachedOrNewDomain(lst.at(i).toElement());
}

Scheme *SchemeXmlDao::find(domain_id_t id)
{
    /** Try to get from cache at first */
    Scheme* result = cache[id];

    if (result != NULL) return result;

    QDomNode node = findXmlNode(id);
    if (node.isNull() == false)
        result = newCachedDomain(node.toElement());

    return result;
}

void SchemeXmlDao::findByTitle(const domain_title_t &title, QList<Scheme *> *result)
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

void SchemeXmlDao::findByDescription(const domain_descr_t &descr, QList<Scheme *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    domain_descr_t tmp_descr;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_descr = descriptionFromXmlElement(elem);
        if (tmp_descr == descr)
            (*result) << cachedOrNewDomain(elem);
    }
}

void SchemeXmlDao::findByModel(const Model *model, QList<Scheme *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    domain_id_t tmp_id;
    domain_id_t model_id = model->id;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_id = modelIdFromXmlElement(elem);

        if (tmp_id == model_id)
            (*result) << cachedOrNewDomain(elem);
    }
}

void SchemeXmlDao::update(Scheme *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        QDomNode root = parentNode(domain);
        if (root.isNull()) return;

        if (node.parentNode() != root)
        {
            node.parentNode().removeChild(node);
            root.appendChild(node);
        }

        QDomElement elem = node.toElement();
        domainToXmlElement(domain, &elem);
    }
}

void SchemeXmlDao::remove(Scheme *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        node.parentNode().removeChild(node);
        removeFromCachedAndDispose(domain->id);
    }
}

void SchemeXmlDao::loadModel(Scheme *domain)
{
    Model* model = NULL;

    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        domain_id_t id =  modelIdFromXmlElement(node.toElement());
        model = modelDao.find(id);
    }

    domain->setModel(model);
}

Scheme *SchemeXmlDao::cachedOrNewDomain(const QDomElement &element)
{
    domain_id_t id = idFromXmlElement(element);
    Scheme* result = cache[id];

    if (result == NULL)
        result = newCachedDomain(element);

    return result;
}

Scheme *SchemeXmlDao::newCachedDomain(const QDomElement &element)
{
    Scheme* result = new Scheme(this);

    result->id    = idFromXmlElement(element);
    result->title = titleFromXmlElement(element);
    result->description = descriptionFromXmlElement(element);

    cache[result->id] = result;

    return result;
}

void SchemeXmlDao::domainToXmlElement(Scheme *domain, QDomElement *element)
{
    idToXmlElement(domain->id, element);
    titleToXmlElement(domain->title, element);
    descriptionToXmlElement(domain->description, element);
    modelIdToXmlElement(domain->model()->id, element);
}

void SchemeXmlDao::removeFromCachedAndDispose(domain_id_t id)
{
    Scheme* cached = cache[id];
    if (cached != NULL)
    {
        cache.remove(id);
        delete cached;
    }
}

QDomNode SchemeXmlDao::parentNode(Scheme *domain)
{
    QDomNode result;

    forever
    {
        Model* model = domain->model();
        if (model == NULL) break;

        QDomNode modelNode = modelDao.findXmlNode(model->id);
        if (modelNode.isNull())
            break;

        result = modelNode;

        break;
    }

    return result;
}

QString SchemeXmlDao::tagNameRaw()
{
    return m_tagName;
}

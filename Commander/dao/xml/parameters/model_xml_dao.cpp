#include "model_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

domain_id_t ModelXmlDao::currentId  = 0;
QString ModelXmlDao::tagName        = "ParameterModel";
QMap<domain_id_t, Model*> ModelXmlDao::cache;

ModelXmlDao::ModelXmlDao()
{
}

ModelXmlDao::~ModelXmlDao()
{
}

void ModelXmlDao::all(QList<Model *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    Model* model;
    domain_id_t id;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        id = idFromXmlElement(elem);

        /** Try to get from cache at first */
        model = cache[id];

        if (model == NULL)
        {
            model = new Model;
            model->id    = id;
            model->kind  = elem.attribute(XML_ATTR_KIND,  "0").toInt();
            model->title = titleFromXmlElement(elem);

            /** Put to cache */
            cache[id] = model;
        }

        (*result) << model;
    }
}

void ModelXmlDao::save(Model* domain)
{
    /** Check existance in cache */
    if (cache[domain->id] != NULL) return;

    domain->id = newId();

    /** Put to cache */
    cache[domain->id] = domain;

    QDomElement root = dsDoc.documentElement();
    QDomElement elem = dsDoc.createElement(tagName);

    idToXmlElement(domain->id, &elem);
    titleToXmlElement(domain->title, &elem);
    elem.setAttribute(XML_ATTR_KIND,  QString::number(domain->kind));

    root.appendChild(elem);
}

Model* ModelXmlDao::find(domain_id_t id)
{
    /** Try to get from cache at first */
    Model* result = cache[id];

    if (result != NULL) return result;

    QDomNode node = findXmlNode(id);
    if (node.isNull() == false)
    {
        QDomElement elem = node.toElement();

        result = new Model;
        result->id    = id;
        result->kind  = elem.attribute(XML_ATTR_KIND,  "0").toInt();
        result->title = titleFromXmlElement(elem);

        /** Put to cache */
        cache[id] = result;
    }

    return result;
}

void ModelXmlDao::findByTitle(const domain_title_t& title, QList<Model *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_id_t id;
    domain_title_t tmp_title;

    Model* model;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_title = titleFromXmlElement(elem);
        if (tmp_title == title)
        {
            id = idFromXmlElement(elem);

            /** Try to get from cache at first */
            model = cache[id];

            if (model == NULL)
            {
                model = new Model;

                model->id    = id;
                model->kind  = elem.attribute(XML_ATTR_KIND,  "0").toInt();
                model->title = title;

                /** Put to cache */
                cache[id] = model;
            }

            (*result) << model;
        }
    }
}

void ModelXmlDao::findByKind(domain_kind_t kind, QList<Model *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_id_t id;
    domain_kind_t tmp_kind;

    Model* model;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_kind = elem.attribute(XML_ATTR_KIND, "0").toInt();

        if (tmp_kind == kind)
        {
            id = idFromXmlElement(elem);

            /** Try to get from cache at first */
            model = cache[id];

            if (model == NULL)
            {
                model = new Model;

                model->id    = id;
                model->kind  = kind;
                model->title = titleFromXmlElement(elem);

                /** Put to cache */
                cache[id] = model;
            }

            (*result) << model;
        }
    }
}

void ModelXmlDao::update(const Model *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        QDomElement elem = node.toElement();

        titleToXmlElement(domain->title, &elem);
        elem.setAttribute(XML_ATTR_KIND,  QString::number(domain->kind));
    }
}

void ModelXmlDao::remove(const Model *domain)
{
    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        node.parentNode().removeChild(node);

        /** Remove from cache */
        Model* cached = cache[domain->id];
        if (cached != NULL)
        {
            cache.remove(domain->id);
            delete cached;
        }
    }
}

QDomNode ModelXmlDao::findXmlNode(domain_id_t id)
{
    domain_id_t tmp_id;
    QDomElement elem;
    QDomNode node;

    QDomNode result;
    result.clear();

    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    for (int i = 0; i < lst.count(); ++i)
    {
        node = lst.at(i);
        elem = node.toElement();
        tmp_id = idFromXmlElement(elem);
        if (tmp_id == id)
        {
            result = node;
            break;
        }
    }

    return result;
}

void ModelXmlDao::clearCache()
{
    cache.clear();
}

domain_id_t ModelXmlDao::newId()
{
    if (currentId==0)
        initId();

    return ++currentId;
}

void ModelXmlDao::initId()
{
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    domain_id_t tmp_id;

    for (int i = 0; i < lst.count(); ++i)
    {
        tmp_id = idFromXmlElement(lst.at(i).toElement());
        currentId = qMax(tmp_id, currentId);
    }
}

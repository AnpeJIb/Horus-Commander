#include "model_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

domain_id_t ModelXmlDao::currentId  = 0;
QString ModelXmlDao::tagName        = "ParameterModel";
QMap<domain_id_t, Model*> ModelXmlDao::cache;

ModelXmlDao::ModelXmlDao()
{
}

void ModelXmlDao::all(QList<Model *> *result)
{
    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    Model* model;
    domain_id_t id;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        id = elem.attribute(XML_ATTR_ID, "0").toULongLong();

        /** Try to get from cache at first */
        model = cache[id];

        if (model == NULL)
        {
            model = new Model;
            model->id    = id;
            model->kind  = elem.attribute(XML_ATTR_KIND,  "0").toInt();
            model->title = elem.attribute(XML_ATTR_TITLE, "");

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

    elem.setAttribute(XML_ATTR_ID,    domain->id);
    elem.setAttribute(XML_ATTR_TITLE, domain->title);
    elem.setAttribute(XML_ATTR_KIND,  QString::number(domain->kind));

    root.appendChild(elem);
}

Model* ModelXmlDao::find(domain_id_t id)
{
    /** Try to get from cache at first */
    Model* result = cache[id];

    if (result != NULL) return result;

    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_id_t tmp_id;

    bool found = false;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_id = elem.attribute(XML_ATTR_ID, "0").toULongLong();
        if (tmp_id == id)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        result = new Model;
        result->id    = tmp_id;
        result->kind  = elem.attribute(XML_ATTR_KIND,  "0").toInt();
        result->title = elem.attribute(XML_ATTR_TITLE, "");

        /** Put to cache */
        cache[id] = result;
    }

    return result;
}

void ModelXmlDao::findByTitle(const domain_title_t& title, QList<Model *> *result)
{
    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_id_t id;
    domain_title_t tmp_title;    

    Model* model;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_title = elem.attribute(XML_ATTR_TITLE, "");
        if (tmp_title == title)
        {
            id = elem.attribute(XML_ATTR_ID, "0").toULongLong();

            /** Try to get from cache at first */
            model = cache[id];

            if (model == NULL)
            {
                model = new Model;

                model->id    = id;
                model->kind  = elem.attribute(XML_ATTR_KIND,  "0").toInt();
                model->title = tmp_title;

                /** Put to cache */
                cache[id] = model;
            }

            (*result) << model;
        }
    }
}

void ModelXmlDao::findByKind(domain_kind_t kind, QList<Model *> *result)
{
    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

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
            id = elem.attribute(XML_ATTR_ID, "0").toULongLong();

            /** Try to get from cache at first */
            model = cache[id];

            if (model == NULL)
            {
                model = new Model;

                model->id    = id;
                model->kind  = kind;
                model->title = elem.attribute(XML_ATTR_TITLE, "");

                /** Put to cache */
                cache[id] = model;
            }

            (*result) << model;
        }
    }
}

void ModelXmlDao::update(const Model *domain)
{
    bool found = false;

    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_id_t tmp_id;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_id = elem.attribute(XML_ATTR_ID, "0").toULongLong();
        if (tmp_id == domain->id)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        elem.setAttribute(XML_ATTR_TITLE, domain->title);
        elem.setAttribute(XML_ATTR_KIND,  QString::number(domain->kind));
    }
}

void ModelXmlDao::remove(const Model *domain)
{
    bool found = false;

    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomNode node;
    QDomElement elem;
    domain_id_t tmp_id;

    for (int i = 0; i < lst.count(); ++i)
    {
        node = lst.at(i);
        elem = node.toElement();
        tmp_id = elem.attribute(XML_ATTR_ID, "0").toULongLong();
        if (tmp_id == domain->id)
        {
            found = true;
            break;
        }
    }

    if (found)
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

domain_id_t ModelXmlDao::newId()
{
    if (currentId==0)
        initId();

    return ++currentId;
}

void ModelXmlDao::initId()
{
    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    domain_id_t tmp_id;

    for (int i = 0; i < lst.count(); ++i)
    {
        tmp_id = lst.at(i).toElement().attribute(XML_ATTR_ID, "0").toULongLong();
        currentId = qMax(tmp_id, currentId);
    }
}

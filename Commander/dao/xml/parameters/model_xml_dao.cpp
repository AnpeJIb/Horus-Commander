#include "model_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

domain_id_t ModelXmlDao::currentId  = 0;
QString ModelXmlDao::tagName        = "ParameterModel";

ModelXmlDao::ModelXmlDao()
{
}

void ModelXmlDao::all(QList<Model *> *result)
{
    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    Model* model;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();

        model = new Model;

        model->id      = elem.attribute(XML_ATTR_ID,    "0").toULongLong();
        model->kind    = elem.attribute(XML_ATTR_KIND,  "0").toInt();
        model->title   = elem.attribute(XML_ATTR_TITLE, "");

        (*result) << model;
    }
}

void ModelXmlDao::dispose(QList<Model *> *domains)
{
    foreach (Model* m, *domains)
    {
        domains->removeOne(m);
        delete m;
    }
}

void ModelXmlDao::save(Model* domain)
{
    domain->id = newId();

    QDomElement root = dsDoc.documentElement();
    QDomElement elem = dsDoc.createElement(tagName);

    elem.setAttribute(XML_ATTR_ID,      domain->id);
    elem.setAttribute(XML_ATTR_TITLE,   domain->title);
    elem.setAttribute(XML_ATTR_KIND,    QString::number(domain->kind));

    root.appendChild(elem);
}

bool ModelXmlDao::find(domain_id_t id, Model* result)
{
    bool found = false;

    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_id_t tmp_id;

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
        result->id      = tmp_id;
        result->kind    = elem.attribute(XML_ATTR_KIND,  "0").toInt();
        result->title   = elem.attribute(XML_ATTR_TITLE, "");
    }

    return found;
}

void ModelXmlDao::findByTitle(const domain_title_t& title, QList<Model *> *result)
{
    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_title_t tmp_title;

    Model* model;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_title = elem.attribute(XML_ATTR_TITLE, "");
        if (tmp_title == title)
        {
            model = new Model;

            model->id      = elem.attribute(XML_ATTR_ID, "0").toULongLong();
            model->kind    = elem.attribute(XML_ATTR_KIND,  "0").toInt();
            model->title   = tmp_title;

            (*result) << model;
        }
    }
}

void ModelXmlDao::findByKind(domain_kind_t kind, QList<Model *> *result)
{
    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_kind_t tmp_kind;

    Model* model;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_kind = elem.attribute(XML_ATTR_KIND, "0").toInt();
        if (tmp_kind == kind)
        {
            model = new Model;

            model->id      = elem.attribute(XML_ATTR_ID, "0").toULongLong();
            model->kind    = tmp_kind;
            model->title   = elem.attribute(XML_ATTR_TITLE, "");

            (*result) << model;
        }
    }
}

void ModelXmlDao::update(const Model &domain)
{
    bool found = false;

    QDomNodeList lst = ModelXmlDao::dsDoc.elementsByTagName(tagName);

    QDomElement elem;
    domain_id_t tmp_id;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_id = elem.attribute(XML_ATTR_ID, "0").toULongLong();
        if (tmp_id == domain.id)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        elem.setAttribute(XML_ATTR_TITLE,   domain.title);
        elem.setAttribute(XML_ATTR_KIND,    QString::number(domain.kind));
    }
}

void ModelXmlDao::remove(const Model& domain)
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
        if (tmp_id == domain.id)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        node.parentNode().removeChild(node);
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

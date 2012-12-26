#include "scheme_xml_dao.h"

using namespace Dao::Parameters;

QString SchemeXmlDao::m_tagName = "ParameterScheme";

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

Scheme *SchemeXmlDao::newDomain()
{
    return new Scheme(this);
}

void SchemeXmlDao::domainToXmlElement(Scheme *domain, QDomElement *element)
{
    idToXmlElement(domain->id, element);
    titleToXmlElement(domain->title, element);
    descriptionToXmlElement(domain->description, element);
    modelIdToXmlElement(domain->model()->id, element);
}

void SchemeXmlDao::domainFromXmlElement(const QDomElement &element, Scheme *domain)
{
    domain->id    = idFromXmlElement(element);
    domain->title = titleFromXmlElement(element);
    domain->description = descriptionFromXmlElement(element);
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

QString SchemeXmlDao::tagName()
{
    return m_tagName;
}

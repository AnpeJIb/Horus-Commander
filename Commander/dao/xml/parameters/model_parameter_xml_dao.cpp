#include "model_parameter_xml_dao.h"
#include "model_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

QString ModelParameterXmlDao::m_tagName = "Parameter";

void ModelParameterXmlDao::findByTitle(const domain_title_t &title, QList<ModelParameter *> *result)
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

void ModelParameterXmlDao::findByKind(domain_kind_t kind, QList<ModelParameter *> *result)
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

void ModelParameterXmlDao::findByParent(const ModelParameter *parent, QList<ModelParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    domain_id_t tmp_id;
    domain_id_t parent_id = parent->id;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        tmp_id = parentIdFromXmlElement(elem);

        if (tmp_id == parent_id)
            (*result) << cachedOrNewDomain(elem);
    }
}

void ModelParameterXmlDao::findByModel(const Model *model, QList<ModelParameter *> *result)
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

void ModelParameterXmlDao::loadParent(ModelParameter *domain)
{
    ModelParameter* parent = NULL;

    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        domain_id_t id = parentIdFromXmlElement(node.toElement());
        parent = find(id);
    }

    domain->setParent(parent);
}

void ModelParameterXmlDao::loadModel(ModelParameter *domain)
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

void ModelParameterXmlDao::loadSimpleParameter(ModelParameter *domain)
{
    SimpleParameter* parameter = NULL;

    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
    {
        domain_id_t id =  simpleParameterIdFromXmlElement(node.toElement());
        parameter = simpleParameterDao.find(id);
    }

    domain->setSimpleParameter(parameter);
}

ModelParameter *ModelParameterXmlDao::newDomain()
{
    return new ModelParameter(this);
}

void ModelParameterXmlDao::domainToXmlElement(ModelParameter *domain, QDomElement *element)
{
    SimpleParameter* parameter = domain->simpleParameter();
    domain_id_t parameter_id = (parameter == NULL) ? Q_UINT64_C(0) : parameter->id;

    ModelParameter* parent = domain->parent();
    domain_id_t parent_id = (parent == NULL) ? Q_UINT64_C(0) : parent->id;

    idToXmlElement(domain->id, element);
    titleToXmlElement(domain->title, element);
    kindToXmlElement(domain->kind, element);
    modelIdToXmlElement(domain->model()->id, element);
    parentIdToXmlElement(parent_id, element);
    simpleParameterIdToXmlElement(parameter_id, element);
}

void ModelParameterXmlDao::domainFromXmlElement(const QDomElement &element, ModelParameter *domain)
{
    domain->id    = idFromXmlElement(element);
    domain->title = titleFromXmlElement(element);
    domain->kind  = kindFromXmlElement(element);
}

QString ModelParameterXmlDao::tagName()
{
    return m_tagName;
}

QDomNode ModelParameterXmlDao::parentNode(ModelParameter *domain)
{
    QDomNode result;

    forever
    {
        if ((domain->simpleParameter() == NULL) && (domain->kind == Domain::LOGICAL_NONE)) break;
        Model* model = domain->model();
        if (model == NULL) break;

        if (domain->parent() == NULL)
        {
            QDomNode modelNode = modelDao.findXmlNode(model->id);
            if (modelNode.isNull())
                break;

            result = modelNode;
        } else {
            QDomNode parentNode = findXmlNode(domain->parent()->id);
            if (parentNode.isNull())
                break;

            result = parentNode;
        }
        break;
    }

    return result;
}

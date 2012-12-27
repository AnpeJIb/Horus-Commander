#include "model_parameter_xml_dao.h"
#include "model_xml_dao.h"

using namespace Dao::Parameters;

QString ModelParameterXmlDao::m_tagName = "Parameter";

void ModelParameterXmlDao::findByTitle(const domain_title_t &title, QList<ModelParameter *> *result)
{
    findByAttribute((const void*)&title, &isTitleSuitable, result);
}

void ModelParameterXmlDao::findByKind(domain_kind_t kind, QList<ModelParameter *> *result)
{
    findByAttribute((const void*)&kind, &isKindSuitable, result);
}

void ModelParameterXmlDao::findByParent(const ModelParameter *parent, QList<ModelParameter *> *result)
{
    findByAttribute((const void*)&parent->id, &isParentIdSuitable, result);
}

void ModelParameterXmlDao::findByModel(const Model *model, QList<ModelParameter *> *result)
{
    findByAttribute((const void*)&model->id, &isModelIdSuitable, result);
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

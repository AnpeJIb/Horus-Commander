#include "model_parameter_xml_dao.h"
#include "model_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

QString ModelParameterXmlDao::m_tagName = "Parameter";

ModelParameterXmlDao::ModelParameterXmlDao()
{
}

ModelParameterXmlDao::~ModelParameterXmlDao()
{
}

void ModelParameterXmlDao::save(ModelParameter *domain)
{
    /** Check existance in cache */
    if (cache[domain->id] != NULL) return;

    Model* model = domain->model();
    if (model == NULL) return;

    ModelParameter* parent = domain->parent();
    domain_id_t parent_id = (parent == NULL) ? Q_UINT64_C(0) : parent->id;

    SimpleParameter* parameter = domain->simpleParameter();
    if ((parameter == NULL) && (domain->kind == Domain::LOGICAL_NONE)) return;
    domain_id_t parameter_id = (parameter == NULL) ? Q_UINT64_C(0) : parameter->id;

    QDomNode root;

    QDomNode modelNode = modelDao.findXmlNode(model->id);
    if (modelNode.isNull()) return;

    if (parent == NULL)
    {
        root = modelNode;
    } else {
        QDomNodeList lst = modelNode.childNodes();
        QDomNode parentNode;
        bool found = false;

        for (int i = 0; i < lst.count(); ++i)
        {
            parentNode = lst.at(i);
            if (idFromXmlElement(parentNode.toElement()) == parent_id)
            {
                root = parentNode;
                found = true;
                break;
            }
        }

        if (found == false)
            return;
    }

    QDomElement elem = dsDoc.createElement(m_tagName);

    domain->id = newId();

    idToXmlElement(      domain->id,    &elem);
    titleToXmlElement(   domain->title, &elem);
    kindToXmlElement(    domain->kind,  &elem);
    parentIdToXmlElement(parent_id,     &elem);
    modelIdToXmlElement( model->id,     &elem);
    simpleParameterIdToXmlElement(parameter_id, &elem);

    root.appendChild(elem);

    /** Put to cache */
    cache[domain->id] = domain;
}

void ModelParameterXmlDao::all(QList<ModelParameter *> *result)
{
    result->clear();
    QDomNodeList lst = dsDoc.elementsByTagName(m_tagName);

    QDomElement elem;
    ModelParameter* parameter;
    domain_id_t id;

    for (int i = 0; i < lst.count(); ++i)
    {
        elem = lst.at(i).toElement();
        id = idFromXmlElement(elem);

        /** Try to get from cache at first */
        parameter = cache[id];

        if (parameter == NULL)
        {
            parameter = new ModelParameter(this);
            parameter->id    = id;
            parameter->title = titleFromXmlElement(elem);
            parameter->kind  = kindFromXmlElement(elem);

            /** Put to cache */
            cache[id] = parameter;
        }

        (*result) << parameter;
    }
}

ModelParameter *ModelParameterXmlDao::find(domain_id_t id)
{
    /** Try to get from cache at first */
    ModelParameter* result = cache[id];

    if (result != NULL) return result;

    QDomNode node = findXmlNode(id);
    if (node.isNull() == false)
    {
        QDomElement elem = node.toElement();

        result = new ModelParameter(this);
        result->id    = id;
        result->title = titleFromXmlElement(elem);
        result->kind  = kindFromXmlElement(elem);

        /** Put to cache */
        cache[id] = result;
    }

    return result;
}

void ModelParameterXmlDao::findByTitle(const domain_title_t &title, QList<ModelParameter *> *result)
{
}

void ModelParameterXmlDao::findByKind(domain_kind_t kind, QList<ModelParameter *> *result)
{
}

void ModelParameterXmlDao::findByParent(const ModelParameter *parent, QList<ModelParameter *> *result)
{
}

void ModelParameterXmlDao::findByModel(const Model *model, QList<ModelParameter *> *result)
{
}

void ModelParameterXmlDao::update(const ModelParameter *domain)
{
}

void ModelParameterXmlDao::remove(const ModelParameter *domain)
{
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

QString ModelParameterXmlDao::tagNameRaw()
{
    return m_tagName;
}

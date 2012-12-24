#include "model_parameter_xml_dao.h"
#include "model_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

domain_id_t ModelParameterXmlDao::currentId = 0;
QString ModelParameterXmlDao::tagName       = "Parameter";
QMap<domain_id_t, ModelParameter*> ModelParameterXmlDao::cache;

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

    SimpleParameter* parameter = domain->simpleParameter();
    if (parameter == NULL) return;

    QDomNode root;

    QDomNode modelNode = modelDao.findXmlNode(model->id);
    if (modelNode.isNull()) return;

    ModelParameter* parent = domain->parent();
    domain_id_t parent_id = (parent == NULL) ? Q_UINT64_C(0) : parent->id;

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

    QDomElement elem = dsDoc.createElement(tagName);

    domain->id = newId();

    idToXmlElement(domain->id, &elem);
    titleToXmlElement(domain->title, &elem);
    kindToXmlElement(domain->kind, &elem);
    parentIdToXmlElement(parent_id, &elem);
    elem.setAttribute(XML_ATTR_MODEL_ID,  QString::number(model->id));
    elem.setAttribute(XML_ATTR_SIMPLE_PARAMETER_ID, QString::number(parameter->id));

    root.appendChild(elem);

    /** Put to cache */
    cache[domain->id] = domain;
}

void ModelParameterXmlDao::all(QList<ModelParameter *> *result)
{
}

ModelParameter *ModelParameterXmlDao::find(domain_id_t id)
{
    /** Try to get from cache at first */
    ModelParameter* result = cache[id];

    if (result != NULL) return result;

    // TODO:

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

domain_id_t ModelParameterXmlDao::newId()
{
    if (currentId==0)
        initId();

    return ++currentId;
}

void ModelParameterXmlDao::initId()
{
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    domain_id_t tmp_id;

    for (int i = 0; i < lst.count(); ++i)
    {
        tmp_id = idFromXmlElement(lst.at(i).toElement());
        currentId = qMax(tmp_id, currentId);
    }
}

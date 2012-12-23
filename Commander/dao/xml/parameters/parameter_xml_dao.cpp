#include "parameter_xml_dao.h"
#include "model_xml_dao.h"
#include "xml_dao_helper.h"

using namespace Dao::Parameters;

domain_id_t ParameterXmlDao::currentId = 0;
QString ParameterXmlDao::tagName       = "Parameter";
QMap<domain_id_t, Parameter*> ParameterXmlDao::cache;

ParameterXmlDao::ParameterXmlDao()
{
}

ParameterXmlDao::~ParameterXmlDao()
{
}

void ParameterXmlDao::save(Parameter *domain)
{
    /** Check existance in cache */
    if (cache[domain->id] != NULL) return;

    Model* model = domain->model();

    QDomNode root;

    QDomNode modelNode = modelDao.findXmlNode(model->id);
    if (modelNode.isNull()) return;

    Parameter* parent = domain->parent();
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
            if (parentNode.toElement().attribute(XML_ATTR_ID, "0").toULongLong() == parent_id)
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

    elem.setAttribute(XML_ATTR_ID,        QString::number(domain->id));
    elem.setAttribute(XML_ATTR_TITLE,     domain->title);
    elem.setAttribute(XML_ATTR_CODE_NAME, domain->codeName);
    elem.setAttribute(XML_ATTR_KIND,      QString::number(domain->kind));
    elem.setAttribute(XML_ATTR_PARENT_ID, QString::number(parent_id));
    elem.setAttribute(XML_ATTR_MODEL_ID,  QString::number(model->id));

    root.appendChild(elem);

    /** Put to cache */
    cache[domain->id] = domain;
}

void ParameterXmlDao::all(QList<Parameter *> *result)
{
}

Parameter *ParameterXmlDao::find(domain_id_t id)
{
    /** Try to get from cache at first */
    Parameter* result = cache[id];

    if (result != NULL) return result;

    // TODO:

    return result;
}

void ParameterXmlDao::findByTitle(const domain_title_t &title, QList<Parameter *> *result)
{
}

void ParameterXmlDao::findByKind(domain_kind_t kind, QList<Parameter *> *result)
{
}

void ParameterXmlDao::findByCodeName(domain_codeName_t codeName, QList<Parameter *> *result)
{
}

void ParameterXmlDao::findByParent(const Parameter *parent, QList<Parameter *> *result)
{
}

void ParameterXmlDao::findByModel(const Model *model, QList<Parameter *> *result)
{
}

void ParameterXmlDao::update(const Parameter *domain)
{
}

void ParameterXmlDao::remove(const Parameter *domain)
{
}

domain_id_t ParameterXmlDao::newId()
{
    if (currentId==0)
        initId();

    return ++currentId;
}

void ParameterXmlDao::initId()
{
    QDomNodeList lst = dsDoc.elementsByTagName(tagName);

    domain_id_t tmp_id;

    for (int i = 0; i < lst.count(); ++i)
    {
        tmp_id = lst.at(i).toElement().attribute(XML_ATTR_ID, "0").toULongLong();
        currentId = qMax(tmp_id, currentId);
    }
}

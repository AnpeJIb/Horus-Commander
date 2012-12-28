#include "scheme_xml_dao.h"

using namespace Dao::Parameters;

QString SchemeXmlDao::m_tagName = "ParameterScheme";

void SchemeXmlDao::findByTitle(const domain_title_t &title, QList<Scheme *> *result)
{
    findByAttribute((const void*)&title, &isTitleSuitable, result);
}

void SchemeXmlDao::findByDescription(const domain_descr_t &descr, QList<Scheme *> *result)
{
    findByAttribute((const void*)&descr, &isDescriptionSuitable, result);
}

void SchemeXmlDao::findByModel(const Model *model, QList<Scheme *> *result)
{
    findByAttribute((const void*)&model->id, &isModelIdSuitable, result);
}

void SchemeXmlDao::loadModel(Scheme *domain)
{
    Model* model = NULL;

    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
        model = modelDao.find(modelIdFromXmlElement(node.toElement()));

    domain->setModel(model);
}

SchemeXmlDao *SchemeXmlDao::clone() const
{
    return new SchemeXmlDao;
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

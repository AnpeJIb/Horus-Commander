#include "model_parameter_value_xml_dao.h"

using namespace Dao::Parameters;

QString ModelParameterValueXmlDao::m_tagName = "ParameterValue";


void ModelParameterValueXmlDao::findByScheme(const Scheme *scheme, QList<ModelParameterValue *> *result)
{
    findByAttribute((const void*)&scheme->id, &isSchemeIdSuitable, result);
}

void ModelParameterValueXmlDao::findByModelParameter(const ModelParameter *parameter, QList<ModelParameterValue *> *result)
{
    findByAttribute((const void*)&parameter->id, &isModelParameterIdSuitable, result);
}

void ModelParameterValueXmlDao::findByValue(const QString &value, QList<ModelParameterValue *> *result)
{
    findByAttribute((const void*)&value, &isValueSuitable, result);
}

void ModelParameterValueXmlDao::findByCodeNameForScheme(
        const domain_codeName_t &codemane, const Scheme *scheme, QList<ModelParameterValue *> *result)
{
    result->clear();

    QList<ModelParameter *> mParams;
    parameterDao.findByCodeName(codemane, &mParams);

    if (mParams.count() == 0) return;

    QList<ModelParameterValue *> values;

    foreach (ModelParameter* mp, mParams)
    {
        findByModelParameter(mp, &values);
        if (values.count() == 0) continue;

        foreach (ModelParameterValue* value, values)
        {
            if (value->scheme() == scheme)
                (*result) << value;
        }
    }
}

void ModelParameterValueXmlDao::loadScheme(ModelParameterValue *domain)
{
    Scheme* scheme = NULL;

    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
        scheme = schemeDao.find(schemeIdFromXmlElement(node.toElement()));

    domain->setScheme(scheme);
}

void ModelParameterValueXmlDao::loadModelParameter(ModelParameterValue *domain)
{
    ModelParameter* parameter = NULL;

    QDomNode node = findXmlNode(domain->id);
    if (node.isNull() == false)
        parameter = parameterDao.find(modelParameterIdFromXmlElement(node.toElement()));

    domain->setParameter(parameter);
}

ModelParameterValueXmlDao *ModelParameterValueXmlDao::clone() const
{
    return new ModelParameterValueXmlDao;
}

ModelParameterValue *ModelParameterValueXmlDao::newDomain()
{
    return new ModelParameterValue(this);
}

void ModelParameterValueXmlDao::domainToXmlElement(ModelParameterValue *domain, QDomElement *element)
{
    idToXmlElement(domain->id, element);
    schemeIdToXmlElement(domain->scheme()->id, element);
    modelParameterIdToXmlElement(domain->parameter()->id, element);
    valueToXmlElement(domain->value, element);
}

void ModelParameterValueXmlDao::domainFromXmlElement(const QDomElement &element, ModelParameterValue *domain)
{
    domain->id    = idFromXmlElement(element);
    domain->value = valueFromXmlElement(element);
}

QDomNode ModelParameterValueXmlDao::parentNode(ModelParameterValue *domain)
{
    QDomNode result;

    forever
    {
        Scheme* scheme = domain->scheme();
        if (scheme == NULL) break;

        QDomNode schemeNode = schemeDao.findXmlNode(scheme->id);
        if (schemeNode.isNull())
            break;

        result = schemeNode;
        break;
    }

    return result;
}

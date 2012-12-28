#ifndef MODEL_PARAMETER_VALUE_XML_DAO_H
#define MODEL_PARAMETER_VALUE_XML_DAO_H

#include "xml_dao.h"

#include "model_parameter_value.h"
#include "model_parameter_value_dao.h"

#include "model_parameter_xml_dao.h"
#include "scheme_xml_dao.h"
#include "scheme_carrier_xml_dao.h"

#define XML_ATTR_MODEL_PARAMETER_ID "model_parameter_id"
#define XML_ATTR_VALUE              "value"

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class ModelParameterValueXmlDao;

class ModelParameterValueXmlDao:
        public XmlDao<ModelParameterValue, ModelParameterValueXmlDao>,
        public ModelParameterValueDao,
        public SchemeCarrierXmlDao
{
public:
    ModelParameterValueXmlDao(){}
    ~ModelParameterValueXmlDao(){}

    static QString tagName()                       { return m_tagName;  }

    void save(ModelParameterValue* domain)         { doSave(domain);    }
    void all(QList<ModelParameterValue *> *result) { doAll(result);     }
    ModelParameterValue* find(domain_id_t id)      { return doFind(id); }

    void update(ModelParameterValue *domain)       { doUpdate(domain);  }
    void remove(ModelParameterValue* domain)       { doRemove(domain);  }

    void findByScheme(const Scheme *scheme, QList<ModelParameterValue *> *result);
    void findByModelParameter(const ModelParameter *parameter, QList<ModelParameterValue *> *result);
    void findByValue(const QString &value, QList<ModelParameterValue *> *result);

    void loadScheme(ModelParameterValue* domain);
    void loadModelParameter(ModelParameterValue* domain);

    ModelParameterValueXmlDao* clone() const;

protected:
    ModelParameterValue* newDomain();
    void domainToXmlElement(ModelParameterValue *domain, QDomElement* element);
    void domainFromXmlElement(const QDomElement& element, ModelParameterValue* domain);
    QDomNode parentNode(ModelParameterValue *domain);

private:
    static QString m_tagName;

    static domain_id_t modelParameterIdFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_MODEL_PARAMETER_ID, "0").toULongLong();
    }

    static void modelParameterIdToXmlElement(domain_id_t id, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_MODEL_PARAMETER_ID, QString::number(id));
    }

    static bool isModelParameterIdSuitable(const void* id, const QDomElement &element)
    {
        return (*(domain_id_t*)(id)) == modelParameterIdFromXmlElement(element);
    }

    static QString valueFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_VALUE, QObject::tr("No value"));
    }

    static void valueToXmlElement(const QString& value, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_VALUE, value);
    }

    static bool isValueSuitable(const void* value, const QDomElement &element)
    {
        return (*(QString*)value) == valueFromXmlElement(element);
    }

    ModelParameterXmlDao parameterDao;
    SchemeXmlDao schemeDao;
};

}}

#endif // MODEL_PARAMETER_VALUE_XML_DAO_H

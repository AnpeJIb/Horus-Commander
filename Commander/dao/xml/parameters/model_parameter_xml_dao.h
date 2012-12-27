#ifndef MODEL_PARAMETER_XML_DAO_H
#define MODEL_PARAMETER_XML_DAO_H

#include "xml_dao.h"
#include "model_xml_dao.h"
#include "simple_parameter_xml_dao.h"
#include "model_parameter.h"
#include "model_parameter_dao.h"
#include "title_carrier_xml_dao.h"
#include "kind_carrier_xml_dao.h"
#include "parent_carrier_xml_dao.h"
#include "model_carrier_xml_dao.h"

#define XML_ATTR_SIMPLE_PARAMETER_ID "simple_parameter_id"

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class ModelParameterXmlDao;

class ModelParameterXmlDao:
        public XmlDao<ModelParameter, ModelParameterXmlDao>,
        public ModelParameterDao,
        public TitleCarrierXmlDao,
        public KindCarrierXmlDao,
        public ParentCarrierXmlDao,
        public ModelCarrierXmlDao
{
public:
    ModelParameterXmlDao(){}
    ~ModelParameterXmlDao(){}

    void save(ModelParameter* domain)         { doSave(domain);    }
    void all(QList<ModelParameter *> *result) { doAll(result);     }
    ModelParameter* find(domain_id_t id)      { return doFind(id); }

    void update(ModelParameter *domain)       { doUpdate(domain);  }
    void remove(ModelParameter* domain)       { doRemove(domain);  }

    void findByTitle(const domain_title_t& title, QList<ModelParameter *> *result);
    void findByKind(domain_kind_t kind, QList<ModelParameter *> *result);
    void findByParent(const ModelParameter* parent, QList<ModelParameter *> *result);
    void findByModel(const Model* model, QList< ModelParameter* >* result);

    void loadParent(ModelParameter* domain);
    void loadModel(ModelParameter* domain);
    void loadSimpleParameter(ModelParameter* domain);

    static QString tagName();

protected:
    ModelParameter* newDomain();
    void domainToXmlElement(ModelParameter *domain, QDomElement* element);
    void domainFromXmlElement(const QDomElement& element, ModelParameter* domain);
    QDomNode parentNode(ModelParameter *domain);

private:
    static QString m_tagName;

    inline domain_id_t simpleParameterIdFromXmlElement(const QDomElement& element)
    {
        return element.attribute(XML_ATTR_SIMPLE_PARAMETER_ID, "0").toULongLong();
    }

    inline void simpleParameterIdToXmlElement(domain_id_t id, QDomElement* element)
    {
        element->setAttribute(XML_ATTR_SIMPLE_PARAMETER_ID, QString::number(id));
    }

    ModelXmlDao modelDao;
    SimpleParameterXmlDao simpleParameterDao;
};

}}

#endif // MODEL_PARAMETER_XML_DAO_H

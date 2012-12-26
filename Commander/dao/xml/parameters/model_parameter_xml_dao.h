#ifndef MODEL_PARAMETER_XML_DAO_H
#define MODEL_PARAMETER_XML_DAO_H

#include "xml_dao.h"
#include "model_xml_dao.h"
#include "simple_parameter_xml_dao.h"
#include "model_parameter.h"
#include "model_parameter_dao.h"

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class ModelParameterXmlDao;

class ModelParameterXmlDao:
        public XmlDao<ModelParameter, ModelParameterXmlDao>,
        public ModelParameterDao
{
public:
    ModelParameterXmlDao();
    ~ModelParameterXmlDao();

    void save(ModelParameter *domain);

    void all(QList<ModelParameter *> *result);
    ModelParameter* find(domain_id_t id);
    void findByTitle(const domain_title_t& title, QList<ModelParameter *> *result);
    void findByKind(domain_kind_t kind, QList<ModelParameter *> *result);
    void findByParent(const ModelParameter* parent, QList<ModelParameter *> *result);
    void findByModel(const Model* model, QList< ModelParameter* >* result);

    void update(ModelParameter *domain);
    void remove(ModelParameter* domain);

    void loadParent(ModelParameter* domain);
    void loadModel(ModelParameter* domain);
    void loadSimpleParameter(ModelParameter* domain);

    ModelParameter* cachedOrNewDomain(const QDomElement &element);
    ModelParameter* newCachedDomain(const QDomElement& element);
    void domainToXmlElement(ModelParameter *domain, QDomElement* element);

    static QString tagNameRaw();

protected:
    QDomNode parentNode(ModelParameter *domain);

private:
    static QString m_tagName;

    ModelXmlDao modelDao;
    SimpleParameterXmlDao simpleParameterDao;
};

}}

#endif // MODEL_PARAMETER_XML_DAO_H

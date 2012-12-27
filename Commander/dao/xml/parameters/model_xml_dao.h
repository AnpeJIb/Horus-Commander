#ifndef MODEL_XML_DAO_H
#define MODEL_XML_DAO_H

#include "xml_dao.h"
#include "model.h"
#include "model_dao.h"
#include "title_carrier_xml_dao.h"
#include "kind_carrier_xml_dao.h"

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class ModelXmlDao;

class ModelXmlDao:
        public XmlDao<Model, ModelXmlDao>,
        public ModelDao,
        public TitleCarrierXmlDao,
        public KindCarrierXmlDao
{
public:
    ModelXmlDao(){}
    ~ModelXmlDao(){}

    void save(Model* domain)         { doSave(domain);    }
    void all(QList<Model *> *result) { doAll(result);     }
    Model* find(domain_id_t id)      { return doFind(id); }

    void update(Model* domain)       { doUpdate(domain);  }
    void remove(Model* domain)       { doRemove(domain);  }

    void findByTitle(const domain_title_t& title, QList<Model *> *result);
    void findByKind(domain_kind_t kind, QList<Model *> *result);

    static QString tagName();

protected:
    Model* newDomain();
    void domainToXmlElement(Model* domain, QDomElement* element);
    void domainFromXmlElement(const QDomElement& element, Model* domain);
    QDomNode parentNode(Model *domain);

private:
    static QString m_tagName;
};

}}

#endif // MODEL_XML_DAO_H

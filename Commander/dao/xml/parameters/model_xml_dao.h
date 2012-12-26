#ifndef MODEL_XML_DAO_H
#define MODEL_XML_DAO_H

#include "xml_dao.h"
#include "model.h"
#include "model_dao.h"

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class ModelXmlDao;

class ModelXmlDao: public XmlDao<Model, ModelXmlDao>, public ModelDao
{
public:
    ModelXmlDao();
    ~ModelXmlDao();

    void save(Model *domain);

    void all(QList<Model *> *result);
    Model* find(domain_id_t id);
    void findByTitle(const domain_title_t& title, QList<Model *> *result);
    void findByKind(domain_kind_t kind, QList<Model *> *result);

    void update(Model* domain);
    void remove(Model* domain);

    Model* cachedOrNewDomain(const QDomElement& element);
    Model* newCachedDomain(const QDomElement& element);
    void domainToXmlElement(Model* domain, QDomElement* element);
    void removeFromCachedAndDispose(domain_id_t id);

    static QString tagNameRaw();

private:
    static QString m_tagName;
};

}}

#endif // MODEL_XML_DAO_H

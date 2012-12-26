#ifndef SCHEME_XML_DAO_H
#define SCHEME_XML_DAO_H

#include "xml_dao.h"
#include "scheme.h"
#include "scheme_dao.h"
#include "model_xml_dao.h"

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class SchemeXmlDao;

class SchemeXmlDao:
        public XmlDao<Scheme, SchemeXmlDao>,
        public SchemeDao
{
public:
    SchemeXmlDao();
    ~SchemeXmlDao();

    void save(Scheme *domain);

    void all(QList<Scheme *> *result);
    Scheme* find(domain_id_t id);
    void findByTitle(const domain_title_t& title, QList<Scheme *> *result);
    void findByDescription(const domain_descr_t& descr, QList<Scheme *> *result);
    void findByModel(const Model* model, QList< Scheme* >* result);

    void update(Scheme *domain);
    void remove(Scheme* domain);

    void loadModel(Scheme* domain);

    Scheme* cachedOrNewDomain(const QDomElement &element);
    Scheme* newCachedDomain(const QDomElement& element);
    void domainToXmlElement(Scheme *domain, QDomElement* element);

    static QString tagNameRaw();

protected:
    QDomNode parentNode(Scheme *domain);

private:

    static QString m_tagName;

    ModelXmlDao modelDao;
};

}}

#endif // SCHEME_XML_DAO_H

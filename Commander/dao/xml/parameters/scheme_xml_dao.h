#ifndef SCHEME_XML_DAO_H
#define SCHEME_XML_DAO_H

#include "xml_dao.h"
#include "scheme.h"
#include "scheme_dao.h"
#include "model_xml_dao.h"
#include "title_carrier_xml_dao.h"
#include "description_carrier_xml_dao.h"
#include "model_carrier_xml_dao.h"

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class SchemeXmlDao;

class SchemeXmlDao:
        public XmlDao<Scheme, SchemeXmlDao>,
        public SchemeDao,
        public TitleCarrierXmlDao,
        public DescriptionCarrierXmlDao,
        public ModelCarrierXmlDao
{
public:
    SchemeXmlDao(){}
    ~SchemeXmlDao(){}

    static QString tagName()          { return m_tagName;  }

    void save(Scheme* domain)         { doSave(domain);    }
    void all(QList<Scheme *> *result) { doAll(result);     }
    Scheme* find(domain_id_t id)      { return doFind(id); }

    void update(Scheme *domain)       { doUpdate(domain);  }
    void remove(Scheme* domain)       { doRemove(domain);  }

    void findByTitle(const domain_title_t& title, QList<Scheme *> *result);
    void findByDescription(const domain_descr_t& descr, QList<Scheme *> *result);
    void findByModel(const Model* model, QList< Scheme* >* result);
    void findByModelKind(domain_kind_t kind, QList<Scheme *> *result);

    void loadModel(Scheme* domain);
    SchemeXmlDao* clone() const;

protected:
    Scheme* newDomain();
    void domainToXmlElement(Scheme *domain, QDomElement* element);
    void domainFromXmlElement(const QDomElement& element, Scheme* domain);
    QDomNode parentNode(Scheme *domain);

private:

    static QString m_tagName;

    ModelXmlDao modelDao;
};

}}

#endif // SCHEME_XML_DAO_H

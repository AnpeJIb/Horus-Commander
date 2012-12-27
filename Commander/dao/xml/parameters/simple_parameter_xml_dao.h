#ifndef SIMPLE_PARAMETER_XML_DAO_H
#define SIMPLE_PARAMETER_XML_DAO_H

#include "xml_dao.h"
#include "simple_parameter.h"
#include "simple_parameter_dao.h"
#include "title_carrier_xml_dao.h"
#include "code_name_carrier_xml_dao.h"

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class SimpleParameterXmlDao;

class SimpleParameterXmlDao:
        public XmlDao<SimpleParameter, SimpleParameterXmlDao>,
        public SimpleParameterDao,
        public TitleCarrierXmlDao,
        public CodeNameCarrierXmlDao
{
public:
    SimpleParameterXmlDao(){}
    ~SimpleParameterXmlDao(){}

    static QString tagName()                    { return m_tagName;  }

    void save(SimpleParameter* domain)          { doSave(domain);    }
    void all(QList<SimpleParameter *> *result)  { doAll(result);     }
    SimpleParameter* find(domain_id_t id)       { return doFind(id); }

    void update(SimpleParameter* domain)        { doUpdate(domain);  }
    void remove(SimpleParameter* domain)        { doRemove(domain);  }

    void findByTitle(const domain_title_t& title, QList<SimpleParameter *> *result);
    void findByCodeName(const domain_codeName_t& codeName, QList<SimpleParameter *> *result);

protected:
    SimpleParameter* newDomain();
    void domainToXmlElement(SimpleParameter* domain, QDomElement* element);
    void domainFromXmlElement(const QDomElement& element, SimpleParameter* domain);
    QDomNode parentNode(SimpleParameter *domain);

private:
    static QString m_tagName;
};

}}

#endif // SIMPLE_PARAMETER_XML_DAO_H

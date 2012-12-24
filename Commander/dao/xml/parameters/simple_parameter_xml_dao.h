#ifndef SIMPLE_PARAMETER_XML_DAO_H
#define SIMPLE_PARAMETER_XML_DAO_H

#include "xml_dao.h"
#include "simple_parameter.h"
#include "simple_parameter_dao.h"

#include <QMap>

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class SimpleParameterXmlDao: public XmlDao, public SimpleParameterDao
{
public:
    SimpleParameterXmlDao();
    ~SimpleParameterXmlDao();

    void save(SimpleParameter *domain);

    void all(QList<SimpleParameter *> *result);
    SimpleParameter* find(domain_id_t id);
    void findByTitle(const domain_title_t& title, QList<SimpleParameter *> *result);
    void findByCodeName(const domain_codeName_t& codeName, QList<SimpleParameter *> *result);

    void update(const SimpleParameter* domain);
    void remove(const SimpleParameter* domain);

    QDomNode findXmlNode(domain_id_t id);
    static void clearCache();

private:
    static domain_id_t newId();
    static void initId();
    static domain_id_t currentId;

    static QString tagName;
    static QMap<domain_id_t, SimpleParameter*> cache;
};

}}

#endif // SIMPLE_PARAMETER_XML_DAO_H

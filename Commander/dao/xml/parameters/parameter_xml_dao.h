#ifndef PARAMETER_XML_DAO_H
#define PARAMETER_XML_DAO_H

#include "parameter.h"
#include "xml_dao.h"
#include "parameter_dao.h"
#include "model_xml_dao.h"

#include <QMap>

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class ParameterXmlDao: public XmlDao, public ParameterDao
{
public:
    ParameterXmlDao();
    ~ParameterXmlDao();

    void save(Parameter *domain);

    void all(QList<Parameter *> *result);
    Parameter* find(domain_id_t id);
    void findByTitle(const domain_title_t& title, QList<Parameter *> *result);
    void findByKind(domain_kind_t kind, QList<Parameter *> *result);
    void findByCodeName(domain_codeName_t codeName, QList<Parameter *> *result);
    void findByParent(const Parameter* parent, QList<Parameter *> *result);
    void findByModel(const Model* model, QList< Parameter* >* result);

    void update(const Parameter* domain);
    void remove(const Parameter* domain);

private:
    static domain_id_t newId();
    static void initId();
    static domain_id_t currentId;
    static QString tagName;

    static QMap<domain_id_t, Parameter*> cache;

    ModelXmlDao modelDao;
};

}}

#endif // PARAMETER_XML_DAO_H

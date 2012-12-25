#ifndef MODEL_PARAMETER_XML_DAO_H
#define MODEL_PARAMETER_XML_DAO_H

#include "xml_dao.h"
#include "model_xml_dao.h"
#include "model_parameter.h"
#include "model_parameter_dao.h"

#include <QMap>

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class ModelParameterXmlDao;

class ModelParameterXmlDao: public XmlDao<ModelParameter, ModelParameterXmlDao>, public ModelParameterDao
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

    void update(const ModelParameter* domain);
    void remove(const ModelParameter* domain);

    static QString tagNameRaw();

private:
    static QString m_tagName;

    ModelXmlDao modelDao;
};

}}

#endif // MODEL_PARAMETER_XML_DAO_H

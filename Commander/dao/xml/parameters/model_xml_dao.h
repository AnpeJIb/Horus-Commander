#ifndef MODEL_XML_DAO_H
#define MODEL_XML_DAO_H

#include "xml_dao.h"
#include "model_dao.h"

namespace Dao { namespace Parameters {

class ModelXmlDao: public XmlDao<Model>, public ModelDao
{
public:
    ModelXmlDao();

    domain_id_t save(Model* domain);

    Model* find(domain_id_t id);
    Model* findByTitle(const domain_title_t& value);
    Model* findByKind(const domain_kind_t& value);

    void update(Model* domain);
    void remove(Model* domain);
};

}}

#endif // MODEL_XML_DAO_H

#ifndef MODEL_XML_DAO_H
#define MODEL_XML_DAO_H

#include "model.h"
#include "xml_dao.h"
#include "model_dao.h"

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class ModelXmlDao: public XmlDao, public ModelDao
{
public:
    ModelXmlDao();

    void save(Model *domain);

    bool find(domain_id_t id, Model *result);
    void findByTitle(const domain_title_t& title, QList<Model*>* result);
    void findByKind(domain_kind_t kind, QList< Model* >* result);

    void update(const Model& domain);
    void remove(const Model &domain);

protected:
    static domain_id_t newId();

private:
    static void initId();
    static domain_id_t currentId;
    static QString tagName;
};

}}

#endif // MODEL_XML_DAO_H
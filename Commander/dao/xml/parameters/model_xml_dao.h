#ifndef MODEL_XML_DAO_H
#define MODEL_XML_DAO_H

#include "model.h"
#include "xml_dao.h"
#include "model_dao.h"

#include <QMap>

namespace Dao { namespace Parameters {

using namespace Domain::Parameters;

class ModelXmlDao: public XmlDao, public ModelDao
{
public:
    ModelXmlDao();
    ~ModelXmlDao();

    void save(Model *domain);

    void all(QList<Model *> *result);
    Model* find(domain_id_t id);
    void findByTitle(const domain_title_t& title, QList<Model *> *result);
    void findByKind(domain_kind_t kind, QList<Model *> *result);

    void update(const Model* domain);
    void remove(const Model* domain);

    QDomNode findXmlNode(domain_id_t id);

private:
    static domain_id_t newId();
    static void initId();
    static domain_id_t currentId;

    static QString tagName;
    static QMap<domain_id_t, Model*> cache;
};

}}

#endif // MODEL_XML_DAO_H

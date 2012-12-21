#include "model_xml_dao.h"

using namespace Dao::Parameters;

ModelXmlDao::ModelXmlDao()
{
}

domain_id_t ModelXmlDao::save(Model* domain)
{
    domain_id_t result = 0;

    // TODO:

    return result;
}

Model* ModelXmlDao::find(domain_id_t id)
{
    Model* result = NULL;

    // TODO:

    return result;
}

Model* ModelXmlDao::findByTitle(const domain_title_t &value)
{
    Model* result = NULL;

    // TODO:

    return result;
}

Model* ModelXmlDao::findByKind(const domain_kind_t &value)
{
    Model* result = NULL;

    // TODO:

    return result;
}

void ModelXmlDao::update(Model* domain)
{
    // TODO:
}

void ModelXmlDao::remove(Model* domain)
{
    // TODO:
}

#ifndef XML_DAO_HELPER_H
#define XML_DAO_HELPER_H

#include <QString>

#include "xml_dao.h"
#include "model_xml_dao.h"
#include "simple_parameter_xml_dao.h"
#include "model_parameter_xml_dao.h"
#include "scheme_xml_dao.h"
#include "model_parameter_value_xml_dao.h"

namespace Dao {

class XmlDaoHelper
{
public:
    static void init(const QString& dataSrcPath);
    static void tearDown();
};

}

#endif // XML_DAO_HELPER_H

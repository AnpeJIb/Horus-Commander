#include "xml_dao_helper.h"

namespace Dao {

void XmlDaoHelper::init(const QString &dataSrcPath)
{
    Dao::XmlDaoBase::init(dataSrcPath);
}

void XmlDaoHelper::tearDown()
{
    Dao::Parameters::ModelXmlDao::clearCacheAndDisposeDomains();
    Dao::Parameters::SimpleParameterXmlDao::clearCacheAndDisposeDomains();
    Dao::Parameters::ModelParameterXmlDao::clearCacheAndDisposeDomains();
    Dao::Parameters::SchemeXmlDao::clearCacheAndDisposeDomains();
    Dao::Parameters::ModelParameterValueXmlDao::clearCacheAndDisposeDomains();

    Dao::Parameters::ModelXmlDao::resetCurrentId();
    Dao::Parameters::SimpleParameterXmlDao::resetCurrentId();
    Dao::Parameters::ModelParameterXmlDao::resetCurrentId();
    Dao::Parameters::SchemeXmlDao::resetCurrentId();
    Dao::Parameters::ModelParameterValueXmlDao::resetCurrentId();
}

}

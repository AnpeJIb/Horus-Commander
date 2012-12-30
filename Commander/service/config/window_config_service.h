#ifndef WINDOW_CONFIG_SERVICE_H
#define WINDOW_CONFIG_SERVICE_H

#include "primary_config_service.h"

#include <QRect>

#include "config_service_base.h"

namespace Service { namespace ConfigService {

class WindowConfigService: public PrimaryConfigService, public ConfigServiceBase
{
public:
    WindowConfigService();

    bool startMinimized();
    bool isMinimized();
    bool quitOnClose();
    bool askQuitConfirmation();
    bool runAsDaemon();
    QRect geometry() const;

    void setStartMinimized(bool value);
    void setMinimized(bool value);
    void setQuitOnClose(bool value);
    void setAskQuitConfirmation(bool value);
    void setRunAsDaemon(bool value);
    void setGeometry(const QRect& value);

protected:
    ModelParameterValueDao* valuesDao()   { return &m_valuesDao;  }
    ModelParameterDao* modelParamsDao()   { return &m_mParamsDao; }
    SimpleParameterDao* simpleParamsDao() { return &m_sParamsDao; }

    Scheme* getCurrentScheme() { return currentScheme(); }
    void syncDao() {Dao::XmlDaoBase::sync();}

private:
    ModelParameterValue* startMinimizedValue();
    ModelParameterValue* quitOnCloseValue();
    ModelParameterValue* askQuitConfirmationValue();
    ModelParameterValue* runAsDaemonValue();

    ModelParameter *rootModelParameter();
    ModelParameter *startMinimizedParameter();
    ModelParameter *quitOnCloseParameter();
    ModelParameter *askQuitConfirmationParameter();
    ModelParameter *runAsDaemonParameter();
};

}}

#endif // WINDOW_CONFIG_SERVICE_H

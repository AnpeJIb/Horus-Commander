#include "window_config_service.h"

#include <QString>

#include "window_config.h"

namespace Service { namespace ConfigService {

const QString GRP_NAME = "Window/";

const QString KEY_IS_MIN = QString(GRP_NAME).append("isMinimized");

const QString KEY_GEOM_X = QString(GRP_NAME).append("x");
const QString KEY_GEOM_Y = QString(GRP_NAME).append("y");
const QString KEY_GEOM_H = QString(GRP_NAME).append("h");
const QString KEY_GEOM_W = QString(GRP_NAME).append("w");

const QString CODE_NAME_ROOT      = "WND_CONFIG";
const QString CODE_NAME_START_MIN = "START_MIN";
const QString CODE_NAME_DO_QUIT   = "DO_QUIT";
const QString CODE_NAME_ASK_QUIT  = "ASK_QUIT";
const QString CODE_NAME_DAEMON    = "DAEMON";

WindowConfigService::WindowConfigService()
{
}

bool WindowConfigService::isMinimized()
{
    return (isInitialized())
            ? m_settings->value(KEY_IS_MIN, Config::Window::defaultIsMinimized).toBool()
            : Config::Window::defaultIsMinimized;
}

bool WindowConfigService::startMinimized()
{
    return (currentScheme() == NULL)?false:startMinimizedValue()->value.toInt() > 0;
}

bool WindowConfigService::quitOnClose()
{
    return (currentScheme() == NULL)?false:quitOnCloseValue()->value.toInt() > 0;
}

bool WindowConfigService::askQuitConfirmation()
{
    return (currentScheme() == NULL)?false:askQuitConfirmationValue()->value.toInt() > 0;
}

bool WindowConfigService::runAsDaemon()
{
    return (currentScheme() == NULL)?false:runAsDaemonValue()->value.toInt() > 0;
}

QRect WindowConfigService::geometry() const
{

    QRect defaultGeom = Config::Window::defaultGeometry;
    if (isInitialized() == false) return defaultGeom;

    QRect geom;

    geom.setX(m_settings->value(KEY_GEOM_X, defaultGeom.x()).toInt());
    geom.setY(m_settings->value(KEY_GEOM_Y, defaultGeom.y()).toInt());
    geom.setHeight(m_settings->value(KEY_GEOM_H, defaultGeom.height()).toInt());
    geom.setWidth( m_settings->value(KEY_GEOM_W, defaultGeom.width() ).toInt());

    return geom;
}

void WindowConfigService::setMinimized(bool value)
{
    if (isInitialized() == false) return;
    m_settings->setValue(KEY_IS_MIN, value);
}

void WindowConfigService::setStartMinimized(bool value)
{
    setValue(startMinimizedValue(), QString::number(value));
}

void WindowConfigService::setQuitOnClose(bool value)
{
    setValue(quitOnCloseValue(), QString::number(value));
}

void WindowConfigService::setAskQuitConfirmation(bool value)
{
    setValue(askQuitConfirmationValue(), QString::number(value));
}

void WindowConfigService::setRunAsDaemon(bool value)
{
    setValue(runAsDaemonValue(), QString::number(value));
}

void WindowConfigService::setGeometry(const QRect &value)
{
    if (isInitialized() == false) return;

    m_settings->setValue(KEY_GEOM_X, value.x());
    m_settings->setValue(KEY_GEOM_Y, value.y());
    m_settings->setValue(KEY_GEOM_H, value.height());
    m_settings->setValue(KEY_GEOM_W, value.width());
}

ModelParameterValue *WindowConfigService::startMinimizedValue()
{
    return getValue(CODE_NAME_START_MIN,
                    QString::number(Config::Window::defaultStartMinimized),
                    startMinimizedParameter());
}

ModelParameterValue *WindowConfigService::quitOnCloseValue()
{
    return getValue(CODE_NAME_DO_QUIT,
                    QString::number(Config::Window::defaultQuitOnlose),
                    quitOnCloseParameter());
}

ModelParameterValue *WindowConfigService::askQuitConfirmationValue()
{
    return getValue(CODE_NAME_ASK_QUIT,
                    QString::number(Config::Window::defaultAskQuitConfirmation),
                    askQuitConfirmationParameter());
}

ModelParameterValue *WindowConfigService::runAsDaemonValue()
{
    return getValue(CODE_NAME_DAEMON,
                    QString::number(Config::Window::defaultRunAsDaemon),
                    runAsDaemonParameter());
}

ModelParameter *WindowConfigService::rootModelParameter()
{
    return modelParameter(CODE_NAME_ROOT, QObject::tr("Window configuration"));
}

ModelParameter *WindowConfigService::startMinimizedParameter()
{
    return modelParameter(CODE_NAME_START_MIN, QObject::tr("Start minimized"), rootModelParameter());
}

ModelParameter *WindowConfigService::quitOnCloseParameter()
{
    return modelParameter(CODE_NAME_DO_QUIT, QObject::tr("Quit on close"), rootModelParameter());
}

ModelParameter *WindowConfigService::askQuitConfirmationParameter()
{
    return modelParameter(CODE_NAME_ASK_QUIT, QObject::tr("Ask quit conformation"), rootModelParameter());
}

ModelParameter *WindowConfigService::runAsDaemonParameter()
{
    return modelParameter(CODE_NAME_DAEMON, QObject::tr("Run as daemon"), rootModelParameter());
}

}}

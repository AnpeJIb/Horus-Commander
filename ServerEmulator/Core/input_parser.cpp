#include "input_parser.h"

InputParser::InputParser(ConsolePrintsCollector* prints_collector, QObject *parent) :
    QObject(parent),
    m_prints_collector(prints_collector)
{
    m_re_mission_load.setPattern("^mission LOAD ([\\w|/]+\\.mis)$");
}

void InputParser::parseString(const QString &str)
{
    if (str.isEmpty()) return;

    if (matchMissionStatus(str)) return;
    if (matchMissionLoad(str)) return;
    if (matchMissionBegin(str)) return;
    if (matchMissionEnd(str)) return;
    if (matchMissionUnload(str)) return;

    if (matchServerInfo(str)) return;
    if (matchExit(str)) return;
    if (matchConsoleQuit(str)) return;

    m_prints_collector->printToConsole(QString("Command not found: %1").arg(str));
}

bool InputParser::matchMissionStatus(const QString &str)
{
    bool result = (str == "mission");
    if (result) emit missionStatusReq();
    return result;
}

bool InputParser::matchMissionLoad(const QString &str)
{
    bool result = m_re_mission_load.exactMatch(str);
    if (result) emit missionLoadReq(m_re_mission_load.cap(1));
    return result;
}

bool InputParser::matchMissionBegin(const QString &str)
{
    bool result = (str == "mission BEGIN");
    if (result) emit missionBeginReq();
    return result;
}

bool InputParser::matchMissionEnd(const QString &str)
{
    bool result = (str == "mission END");
    if (result) emit missionEndReq();
    return result;
}

bool InputParser::matchMissionUnload(const QString &str)
{
    bool result = (str == "mission DESTROY");
    if (result) emit missionUnloadReq();
    return result;
}

bool InputParser::matchServerInfo(const QString &str)
{
    bool result = (str == "server");
    if (result) emit serverInfoReq();
    return result;
}

bool InputParser::matchExit(const QString &str)
{
    bool result = (str == "exit");
    if (result) emit exitReq();
    return result;
}

bool InputParser::matchConsoleQuit(const QString &str)
{
    return (str == "<QUIT QUIT>");
}

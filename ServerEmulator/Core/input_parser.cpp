#include "input_parser.h"

#include <QtGlobal>

InputParser::InputParser(ConsolePrintsCollector* prints_collector, QObject *parent) :
    QObject(parent),
    m_prints_collector(prints_collector),
    m_commands_counter(1)
{
    m_re_mission_load.setPattern("^mission LOAD ([\\w|/]+\\.mis)$");
}

void InputParser::parseString(const QString &str)
{
    if (str.isEmpty()) return;
    if (matchExit(str)) return;

    forever {
        if (matchMissionStatus(str)) break;
        if (matchMissionLoad(str)) break;
        if (matchMissionBegin(str)) break;
        if (matchMissionEnd(str)) break;
        if (matchMissionUnload(str)) break;

        if (matchServerInfo(str)) break;

        m_prints_collector->printToConsole(QString("Command not found: %1").arg(str));

        break;
    }

    m_commands_counter++;
    printPrompt();
}

void InputParser::printPrompt()
{
    m_prints_collector->printToConsole(QString::number(m_commands_counter).append(">"));
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

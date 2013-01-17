#include "input_parser.h"

#include <QtCore>

InputParser::InputParser(QObject *parent) :
    QObject(parent)
{
    m_re_mission_load.setPattern("^mission LOAD ([\\w|/|.]+)");
}

void InputParser::parseString(const QString &str)
{
    if (str.isEmpty()) return;

    QString fixedStr = str;

    if (fixedStr.endsWith('\n'))
        fixedStr.remove(str.length()-1, 1);

    if (matchMissionStatus(fixedStr)) return;
    if (matchMissionLoad(fixedStr)) return;
    if (matchMissionBegin(fixedStr)) return;
    if (matchMissionEnd(fixedStr)) return;
    if (matchMissionUnload(fixedStr)) return;
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

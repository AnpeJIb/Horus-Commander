#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <QObject>
#include <QString>
#include <QRegExp>

#include "console_prints_collector.h"

class InputParser : public QObject
{
    Q_OBJECT
public:
    explicit InputParser(ConsolePrintsCollector* prints_collector, QObject *parent = 0);
    
signals:
    void missionStatusReq();
    void missionLoadReq(QString mission_path);
    void missionBeginReq();
    void missionEndReq();
    void missionUnloadReq();

    void serverInfoReq();
    void exitReq();

public slots:
    void parseString(const QString& str);

private:
    bool matchMissionStatus(const QString& str);
    bool matchMissionLoad(const QString& str);
    bool matchMissionBegin(const QString& str);
    bool matchMissionEnd(const QString& str);
    bool matchMissionUnload(const QString& str);

    bool matchServerInfo(const QString& str);
    bool matchExit(const QString& str);
    bool matchConsoleQuit(const QString& str);

    QRegExp m_re_mission_load;

    ConsolePrintsCollector* m_prints_collector;
};

#endif // INPUT_PARSER_H

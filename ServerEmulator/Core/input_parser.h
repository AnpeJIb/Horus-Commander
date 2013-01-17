#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <QObject>
#include <QString>
#include <QRegExp>

class InputParser : public QObject
{
    Q_OBJECT
public:
    explicit InputParser(QObject *parent = 0);
    
signals:
    void missionStatusReq();
    void missionLoadReq(QString mission_path);
    void missionBeginReq();
    void missionEndReq();
    void missionUnloadReq();

public slots:
    void parseString(const QString& str);

private:
    bool matchMissionStatus(const QString& str);
    bool matchMissionLoad(const QString& str);
    bool matchMissionBegin(const QString& str);
    bool matchMissionEnd(const QString& str);
    bool matchMissionUnload(const QString& str);

    QRegExp m_re_mission_load;
};

#endif // INPUT_PARSER_H

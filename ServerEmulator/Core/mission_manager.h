#ifndef MISSION_MANAGER_H
#define MISSION_MANAGER_H

#include <QObject>
#include <QString>

#include "console_prints_collector.h"
#include "event_file_logger.h"

class MissionManager : public QObject
{
    Q_OBJECT
public:
    explicit MissionManager(ConsolePrintsCollector* prints_collector, EventFileLogger* file_logger);
     
public slots:
    void onMissionStatusReq();
    void onMissionLoadReq(const QString& mission_path);
    void onMissionEndReq();
    void onMissionUnloadReq();

private:
    enum MissionStatus
    {
        MISSION_LOADED,
        MISSION_NOT_LOADED,
        MISSION_PLAYING
    };

    ConsolePrintsCollector* m_prints_collector;
    EventFileLogger* m_file_logger;

    QString m_mission_path;
    MissionStatus m_status;
};

#endif // MISSION_MANAGER_H

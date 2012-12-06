#ifndef MISSIONMANAGER_H
#define MISSIONMANAGER_H

#include <QObject>

class MissionManager: public QObject
{
    Q_OBJECT
public:
    MissionManager();

public slots:
    void start();
    void stop();
};

#endif // MISSIONMANAGER_H

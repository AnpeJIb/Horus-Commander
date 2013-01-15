#ifndef PILOT_MANAGER_H
#define PILOT_MANAGER_H

#include <QString>
#include <QMap>

#include "console_prints_collector.h"

typedef struct
{
    QString callsign;
    QString ip_address;
    int channel_number;
} pilot_info_t;

class PilotManager
{
public:
    PilotManager(const QString& server_stream_port, ConsolePrintsCollector* prints_collector);
    ~PilotManager();

    void pilotJoined(const QString& callsign, const QString& ip_address);
    void pilotLeft(const QString& callsign);

private:
    int newChannelNumber();

    QString m_server_stream_port;
    ConsolePrintsCollector* m_prints_collector;

    int m_current_channel_number;

    QMap<uint, pilot_info_t*> m_pilots_map;
};

#endif // PILOT_MANAGER_H

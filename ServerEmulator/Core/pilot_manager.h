#ifndef PILOT_MANAGER_H
#define PILOT_MANAGER_H

#include <QString>

class PilotManager
{
public:
    PilotManager();

    /** Register new user and get he's channel number */
    int userJoined(const QString& callsign, const QString& ip_address);

private:
    int newChannelNumber();

    int m_current_channel_number;
};

#endif // PILOT_MANAGER_H

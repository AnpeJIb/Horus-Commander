#ifndef WEATHER_REPORT_H
#define WEATHER_REPORT_H

#include <QtCore>
#include <QDateTime>

#include "generic_domain.h"

namespace Domain { namespace Gameflow {

class WeatherReport: public GenericDomain
{
public:

    enum Gust
    {
        GUST_NONE   = 0,
        GUST_WEAK   = 1,
        GUST_AVERAGE= 2,
        GUST_STRONG = 3
    };

    enum Turbulence
    {
        TURB_NONE       = 0,
        TURB_WEAK       = 1,
        TURB_AVERAGE    = 2,
        TURB_STRONG     = 3,
        TURB_VERY_STRONG= 4
    };

    enum Weather
    {
        WEATH_CLOUDLESS     = 0,
        WEATH_CLEAR         = 1,
        WEATH_HAZE          = 2,
        WEATH_SLIGHT_FOG    = 3,
        WEATH_FOG           = 4,
        WEATH_PRECIPITATION = 5,
        WEATH_THUNDER       = 6
    };

    WeatherReport();
    ~WeatherReport();

    /** Clouds height in meters */
    quint16 cloudsHeightM;

    /** Wind direction in degrees */
    quint16 windDirectionDeg;

    /** Wind speed in meters per second */
    quint16 windSpeedMS;

    /** In-game publication datetime */
    QDateTime publGameDT;

    /** Real publication datetime */
    QDateTime publRealDT;

    quint8 gust;
    quint8 turbulence;
    quint8 weather;
};

}}

#endif // WEATHER_REPORT_H

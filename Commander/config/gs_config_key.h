#ifndef GS_CFG_KEY_H
#define GS_CFG_KEY_H

#include "gs_config_group.h"

#define GS_CFG_TRUE     "1"
#define GS_CFG_FALSE    "0"

#define GS_CFG_KEY_AUTO_LOG_DETAIL          GS_CFG_GRP_CHAT     "/autoLogDetail"

#define GS_CFG_KEY_LOG                      GS_CFG_GRP_CONSOLE  "/LOG"
#define GS_CFG_KEY_IP                       GS_CFG_GRP_CONSOLE  "/IP"
#define GS_CFG_KEY_IPS                      GS_CFG_GRP_CONSOLE  "/IPS"

#define GS_CFG_KEY_EVENTLOG                 GS_CFG_GRP_GAME     "/eventlog"
#define GS_CFG_KEY_EVENTLOG_KEEP            GS_CFG_GRP_GAME     "/eventlogkeep"
#define GS_CFG_KEY_EVENTLOG_HOUSE           GS_CFG_GRP_GAME     "/eventlogHouse"
#define GS_CFG_KEY_CHECK_RUNTIME            GS_CFG_GRP_NET      "/checkRuntime"

#define GS_CFG_KEY_SERVER_CHANNELS          GS_CFG_GRP_NET      "/serverChannels"
#define GS_CFG_KEY_SERVER_NAME              GS_CFG_GRP_NET      "/serverName"
#define GS_CFG_KEY_SERVER_DESCR             GS_CFG_GRP_NET      "/serverDescription"

#define GS_CFG_KEY_SKIN                     GS_CFG_GRP_NET      "/SkinDownload"
#define GS_CFG_KEY_CHECK_CLIENT_TIME_SPEED  GS_CFG_GRP_NET      "/checkClientTimeSpeed"
#define GS_CFG_KEY_CHECK_SERVER_TIME_SPEED  GS_CFG_GRP_NET      "/checkServerTimeSpeed"
#define GS_CFG_KEY_CHECK_TIME_SPEED_DIFF    GS_CFG_GRP_NET      "/checkTimeSpeedDifferense"
#define GS_CFG_KEY_CHECK_TIME_SPEED_INTV    GS_CFG_GRP_NET      "/checkTimeSpeedInterval"
#define GS_CFG_KEY_LOCAL_PORT               GS_CFG_GRP_NET      "/localPort"

#define GS_CFG_KEY_CHEAT_WARN_DELAY         GS_CFG_GRP_MAX_LAG  "/cheaterWarningDelay"
#define GS_CFG_KEY_CHEAT_WARN_NUM           GS_CFG_GRP_MAX_LAG  "/cheaterWarningNum"
#define GS_CFG_KEY_CHEAT_FAR_MAX_LAG_TIME   GS_CFG_GRP_MAX_LAG  "/farMaxLagTime"
#define GS_CFG_KEY_CHEAT_NEAR_MAX_LAG_TIME  GS_CFG_GRP_MAX_LAG  "/nearMaxLagTime"

#endif // GS_CFG_KEY_H

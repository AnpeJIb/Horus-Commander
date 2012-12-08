#ifndef GSCOMMAND_H
#define GSCOMMAND_H

#include <QObject>
#include <QString>
#include <QMutex>

#define NEW_LINE                    "\n"
#define GS_CMD_KICK_NUM(NUM)		"kick# " #NUM NEW_LINE
#define GS_CMD_KICK_FIRST			GS_CMD_KICK_NUM(1)

#define GS_CMD_CHAT_MAX_LEN			80
#define GS_CMD_CHAT					"chat \"%s\" %s" NEW_LINE

#define CHAT_ADDRESSEE_ALL			"ALL"
#define CHAT_ADDRESSEE_CALLSIGN		"TO %s"
#define CHAT_ADDRESSEE_USERNUM		"TO# %d"
#define CHAT_ADDRESSEE_ARMY			"ARMY %d"

class GsCommands: public QObject
{
    Q_OBJECT
public:
    static QString get_GC();
    static QString get_RUN_FILE(QString relativePath);
    static QString get_TIMEOUT(int secondsDelay, QString cmd);
    static QString get_EXIT();

    GsCommands(){}

    void init();

    void exit();

    void chatAll(const char *msg);
    void chatCallsign(const char *callsign, const char *msg);
    void chatUsernum(int num, const char *msg);
    void chatArmy(quint8 armyNum, const char *msg);
    void chat(const char *msg, const char *addressee);

    void kickAll();

private:
    void cmdSend(const char *cmd);

    QString m_greetingFormat;
    QString m_aboutCommander;
    QString m_kickingAll;
    QMutex m_txMx;
};

#endif // GSCOMMAND_H

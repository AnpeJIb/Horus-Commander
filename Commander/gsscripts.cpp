#include "gsscripts.h"
#include "servercommander.h"
#include "statusprint.h"
#include "fileext.h"

#include <QObject>
#include <QFile>
#include <QTextStream>

#define GC_SCRIPT_PATH     "gc"     FILE_EXT_CMD
#define MAIN_SCRIPT_PATH   "server" FILE_EXT_CMD
#define USER_SCRIPT_PATH   "user"   FILE_EXT_CMD

static bool generateGC();
static bool generateMain();

bool SC::GS::SCRIPTS::generate()
{
    STATUS_PRINT::NEW(QObject::tr("Generating server's scripts"));

    if (generateGC()==false)
    {
        STATUS_PRINT::FAIL();
        return false;
    }

    if (generateMain()==false)
    {
        STATUS_PRINT::FAIL();
        return false;
    }

    STATUS_PRINT::DONE();
    return true;
}

bool generateGC()
{
    QString fPath = GC_SCRIPT_PATH;

    QFile f(fPath);

    if(f.open(QIODevice::ReadWrite)==false)
    {
        STATUS_PRINT::ERROR(QObject::tr("GC script cannot be created"));
        return false;
    }

    QTextStream ts(&f);

    ts << SC::CMD.get_GC() << endl;
    ts << SC::CMD.get_GC() << endl;
    ts << SC::CMD.get_GC() << endl;

    ts << SC::CMD.get_TIMEOUT(3600000, SC::CMD.get_RUN_FILE(fPath)) << endl;

    f.close();

    return true;
}

bool generateMain()
{
    QString fPath = MAIN_SCRIPT_PATH;

    QFile f(fPath);

    if(f.open(QIODevice::ReadWrite)==false)
    {
        STATUS_PRINT::ERROR(QObject::tr("Main script cannot be created"));
        return false;
    }

    QFile userF(USER_SCRIPT_PATH);

    QTextStream ts(&f);

    ts << SC::CMD.get_RUN_FILE(GC_SCRIPT_PATH)   << endl;

    if (userF.exists())
        ts << SC::CMD.get_RUN_FILE(USER_SCRIPT_PATH) << endl;

    f.close();

    return true;
}

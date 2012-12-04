#include "logs.h"
#include "statusprint.h"
#include "config.h"
#include "fileext.h"

static void UPDATE_LOGGER(StatusPrinter* printer, CommonLogConfig*cfg);

static StatusFileLogger* m_FILE;
static StatusWidget* m_GUI;

void LOGS::INIT()
{
    m_GUI = NULL;

    m_FILE = new StatusFileLogger("horusCommander" FILE_EXT_LOG);
    m_FILE->setLevel(StatusPrinter::ALL);
    STATUS_PRINT::REGISTER(m_FILE);
}

void LOGS::SET_GUI_LOGGER(StatusWidget *value)
{
    m_GUI = value;
}

void LOGS::UPDATE_LOGGERS()
{
    LOGS::UPDATE_FILE_LOGGER();
    LOGS::UPDATE_GUI_LOGGER();
}

void LOGS::UPDATE_FILE_LOGGER() {UPDATE_LOGGER(m_FILE,  CONFIG::LOG.FILE());}
void LOGS::UPDATE_GUI_LOGGER()  {UPDATE_LOGGER(m_GUI,   CONFIG::LOG.GUI());}

void UPDATE_LOGGER(StatusPrinter *printer, CommonLogConfig *cfg)
{
    if (printer==NULL) return;

    if (cfg->isEnable())
        STATUS_PRINT::REGISTER(printer);
    else
        STATUS_PRINT::UNREGISTER(printer);

    printer->setLevel(cfg->level());
}

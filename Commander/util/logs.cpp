#include "logs.h"
#include "statusprint.h"
#include "config.h"
#include "fileext.h"

StatusFileLogger* LOGS::FILE;
StatusWidget* LOGS::GUI;

LOGS::LOGS()
{
    LOGS::GUI = NULL;

    LOGS::FILE = new StatusFileLogger("horusCommander" FILE_EXT_LOG);
    LOGS::FILE->setLevel(StatusPrinter::ALL);
    STATUS_PRINT::REGISTER(LOGS::FILE);
}

void LOGS::SET_GUI_LOGGER(StatusWidget *value)
{
    LOGS::GUI = value;
}

void LOGS::UPDATE_LOGGERS()
{
    LOGS::UPDATE_FILE_LOGGER();
    LOGS::UPDATE_GUI_LOGGER();
}

void LOGS::UPDATE_FILE_LOGGER() {UPDATE_LOGGER(LOGS::FILE,  CONFIG::LOG.FILE());}
void LOGS::UPDATE_GUI_LOGGER()  {UPDATE_LOGGER(LOGS::GUI,   CONFIG::LOG.GUI());}

void LOGS::UPDATE_LOGGER(StatusPrinter *printer, CommonLogConfig *cfg)
{
    if (printer==NULL) return;

    if (cfg->isEnable())
        STATUS_PRINT::REGISTER(printer);
    else
        STATUS_PRINT::UNREGISTER(printer);

    printer->setLevel(cfg->level());
}

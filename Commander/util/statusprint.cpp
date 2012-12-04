#include "statusprint.h"

QList<StatusPrinter*> STATUS_PRINT::printers;

void STATUS_PRINT::REGISTER(StatusPrinter* printer)
{
    if ((printer != NULL) && (STATUS_PRINT::printers.contains(printer)==false))
        STATUS_PRINT::printers.append(printer);
}

void STATUS_PRINT::UNREGISTER(StatusPrinter* printer)
{
    if ((printer != NULL) && (STATUS_PRINT::printers.contains(printer)))
        STATUS_PRINT::printers.removeOne(printer);
}

void STATUS_PRINT::NEW(const QString& str)
{
    foreach(StatusPrinter* printer, STATUS_PRINT::printers)
        printer->statusNew(str);
}

void STATUS_PRINT::DONE()
{
    foreach(StatusPrinter* printer, STATUS_PRINT::printers)
        printer->statusDone();
}

void STATUS_PRINT::FAIL()
{
    foreach(StatusPrinter* printer, STATUS_PRINT::printers)
        printer->statusFail();
}

void STATUS_PRINT::DEBUG_(const QString& str)
{
    foreach(StatusPrinter* printer, STATUS_PRINT::printers)
        printer->msgDebug(str);
}

void STATUS_PRINT::INFO_(const QString& str)
{
    foreach(StatusPrinter* printer, STATUS_PRINT::printers)
        printer->msgInfo(str);
}

void STATUS_PRINT::WARN_(const QString& str)
{
    foreach(StatusPrinter* printer, STATUS_PRINT::printers)
        printer->msgWarn(str);
}

void STATUS_PRINT::ERROR_(const QString& str)
{
    foreach(StatusPrinter* printer, STATUS_PRINT::printers)
        printer->msgError(str);
}

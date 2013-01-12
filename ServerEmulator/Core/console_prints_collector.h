#ifndef CONSOLE_PRINTER_H
#define CONSOLE_PRINTER_H

#include <QObject>
#include <QString>

class ConsolePrintsCollector : public QObject
{
    Q_OBJECT
public:
    explicit ConsolePrintsCollector(QObject *parent = 0): QObject(parent){}

signals:
    void printToConsoleCalled(QString);

public slots:
    void printToConsole(const QString& msg)
    {
        emit printToConsoleCalled(msg);
    }
};

#endif // CONSOLE_PRINTER_H

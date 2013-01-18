#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QFile>
#include <QTextStream>

#include <iostream>

#include "server_emulator.h"

class MainTask : public QObject
{
    Q_OBJECT
public:
    MainTask(QObject *parent = 0) : QObject(parent)
    {
        connect(&m_emulator, SIGNAL(printToConsoleCalled(QString)),
                this, SLOT(onPrintToConsoleCalled(const QString&)), Qt::DirectConnection);
    }

public slots:
    void run()
    {
        QString events_log_path = "events.log";

        m_emulator.configure("127.0.0.1", "20001", events_log_path);
        m_emulator.start();

        QTextStream stream(stdin);
        QString line;
        while((line = stream.readLine()).isNull() == false)
        {
            m_emulator.processExternalInput(line);
        }

        m_emulator.stop();
        m_emulator.wait();

        QFile::remove(events_log_path);

        emit finished();
    }

signals:
    void finished();

private slots:
    void onPrintToConsoleCalled(const QString& msg)
    {
        std::cout << qPrintable(msg) << std::endl;
        std::cout.flush();
    }

private:
    ServerEmulator m_emulator;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    MainTask *task = new MainTask(&a);
    QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, task, SLOT(run()));

    return a.exec();
}

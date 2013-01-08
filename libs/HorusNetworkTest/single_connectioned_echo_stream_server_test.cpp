#include "single_connectioned_echo_stream_server_test.h"

#include <QDateTime>
#include <QtTest/QtTest>

SingleConnectionedEchoStreamServerTest::SingleConnectionedEchoStreamServerTest(QObject *parent) :
    QObject(parent)
{
}

void SingleConnectionedEchoStreamServerTest::initTestCase()
{
    QString address = "127.0.0.1";
    QString port = "10500";

    manager.reset(new StreamServerSingleEchoConnectionManager);
    server.reset(new StreamServer(address, port, io_service, manager));
    server->start();

    client.reset(new StreamClient(io_service));

    connect(client.get(), SIGNAL(connectionSuccess()),
            this, SLOT(onConnectionSuccess()));
    connect(client.get(), SIGNAL(connectionFailure()),
            this, SLOT(onConnectionFailure()));
    connect(client.get(), SIGNAL(connectionLost()),
            this, SLOT(onConnectionLost()));
    connect(client.get(), SIGNAL(messageReceived(QString)),
            this, SLOT(onMessageReceived(QString)));

    updateCurrentMessage();
}

void SingleConnectionedEchoStreamServerTest::testWrongConnection()
{
    client->connect("127.0.0.1", "11111");
    io_service.run();
    QCOMPARE(client->exitCode(), StreamClient::CONNECTION_FAILED);

    io_service.reset();
}

void SingleConnectionedEchoStreamServerTest::testGoodConnection()
{
    client->connect("127.0.0.1", "10500");
    io_service.run();
    QCOMPARE(client->exitCode(), StreamClient::STOPPED_NORMALLY);
}

void SingleConnectionedEchoStreamServerTest::cleanupTestCase()
{
    server->stop();

    client.reset();
    server.reset();
    manager.reset();
}

void SingleConnectionedEchoStreamServerTest::updateCurrentMessage()
{
    m_current_msg = QString("Current time stamp: ")
                  .append(QString::number(QDateTime::currentMSecsSinceEpoch()))
                  .append("\n");
}

void SingleConnectionedEchoStreamServerTest::onConnectionSuccess()
{
    m_messages_left = 1000;
    client->sendMessage(m_current_msg);
}

void SingleConnectionedEchoStreamServerTest::onConnectionFailure()
{
    io_service.stop();
}

void SingleConnectionedEchoStreamServerTest::onConnectionLost()
{
    io_service.stop();
}

void SingleConnectionedEchoStreamServerTest::onMessageReceived(QString msg)
{
    QCOMPARE(msg, m_current_msg);

    if (m_messages_left)
    {
        m_messages_left--;
        updateCurrentMessage();
        client->sendMessage(m_current_msg);
    } else {
        client->disconnect();
        io_service.stop();
    }
}

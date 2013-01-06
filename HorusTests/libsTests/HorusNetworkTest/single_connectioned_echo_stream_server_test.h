#ifndef SINGLE_CONNECTIONED_ECHO_STREAM_SERVER_TEST_H
#define SINGLE_CONNECTIONED_ECHO_STREAM_SERVER_TEST_H

#include <boost/asio.hpp>

#include "stream_client.h"
#include "stream_server.h"
#include "stream_server_single_echo_connection_manager.h"

#include <QObject>

class SingleConnectionedEchoStreamServerTest : public QObject
{
    Q_OBJECT
public:
    explicit SingleConnectionedEchoStreamServerTest(QObject *parent = 0);

public slots:
    void onConnectionSuccess();
    void onConnectionFailure();
    void onConnectionLost();
    void onMessageReceived(QString msg);

private slots:
    void initTestCase();
    void testWrongConnection();
    void testGoodConnection();
    void cleanupTestCase();

private:
    void updateCurrentMessage();

    boost::asio::io_service io_service;
    StreamServerConnectionManager::pointer manager;
    StreamServer::pointer server;
    StreamClient::pointer client;

    QString m_current_msg;
    uint m_messages_left;
};

#endif // SINGLE_CONNECTIONED_ECHO_STREAM_SERVER_TEST_H

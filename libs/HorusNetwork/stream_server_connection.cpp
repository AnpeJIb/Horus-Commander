#include "stream_server_connection.h"

#include <boost/bind.hpp>

StreamServerConnection::StreamServerConnection(boost::asio::io_service &io_service,
        const boost::shared_ptr<StreamServerConnectionManager> &manager)
    : m_socket(io_service),
      m_manager(manager)
{
}

void StreamServerConnection::start()
{
    newReadCycle();
}

void StreamServerConnection::stop()
{
    m_socket.close();
    m_write_msgs.clear();
}

void StreamServerConnection::newReadCycle()
{
    m_rx_data_offset = 0;

    boost::asio::async_read(m_socket,
                            boost::asio::buffer(m_rx_data, 1),
                            boost::bind(&StreamServerConnection::handleReadChar, shared_from_this(),
                                        boost::asio::placeholders::error));
}

void StreamServerConnection::handleReadChar(const boost::system::error_code &error)
{
    if (!error)
    {
        if (m_rx_data[m_rx_data_offset] == '\n')
        {
            m_rx_data[m_rx_data_offset+1] = '\0';
            emit messageReceived(QString(m_rx_data));

            newReadCycle();
        } else {
            boost::asio::async_read(m_socket,
                                    boost::asio::buffer(m_rx_data+(++m_rx_data_offset), 1),
                                    boost::bind(&StreamServerConnection::handleReadChar, shared_from_this(),
                                                boost::asio::placeholders::error));
        }
    } else {
        m_manager->leave(shared_from_this());
    }
}

void StreamServerConnection::sendMessage(const QString &msg)
{
    bool write_in_progress = m_write_msgs.empty() == false;
    m_write_msgs.push_back(msg);

    if (!write_in_progress)
    {
        boost::asio::async_write(m_socket,
                                 boost::asio::buffer(m_write_msgs.front().toStdString().c_str(),
                                                     m_write_msgs.front().toStdString().length()),
                                 boost::bind(&StreamServerConnection::handleWrite, shared_from_this(),
                                             boost::asio::placeholders::error));
    }
}

void StreamServerConnection::handleWrite(const boost::system::error_code &error)
{
    if (!error)
    {
        m_write_msgs.pop_front();
        if (!m_write_msgs.empty())
        {
            boost::asio::async_write(m_socket,
                                     boost::asio::buffer(m_write_msgs.front().toStdString().c_str(),
                                                         m_write_msgs.front().toStdString().length()),
                                     boost::bind(&StreamServerConnection::handleWrite, shared_from_this(),
                                                 boost::asio::placeholders::error));
        }
    } else {
        m_manager->leave(shared_from_this());
    }
}

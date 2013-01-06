#include "stream_connection.h"

#include <boost/bind.hpp>

StreamConnection::StreamConnection(boost::asio::io_service &io_service)
    : m_socket(io_service)
{
}

tcp::socket &StreamConnection::socket()
{
    return m_socket;
}

void StreamConnection::newReadCycle()
{
    m_rx_data_offset = 0;

    boost::asio::async_read(m_socket,
                            boost::asio::buffer(m_rx_data, 1),
                            boost::bind(&StreamConnection::handleReadChar, this,
                                        boost::asio::placeholders::error));
}

void StreamConnection::handleReadChar(const boost::system::error_code &error)
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
                                    boost::bind(&StreamConnection::handleReadChar, this,
                                                boost::asio::placeholders::error));
        }
    } else {
        onErrorOccured();
    }
}

void StreamConnection::sendMessage(const QString &msg)
{
    bool write_in_progress = m_write_msgs.empty() == false;
    m_write_msgs.push_back(msg);

    if (!write_in_progress)
    {
        boost::asio::async_write(m_socket,
                                 boost::asio::buffer(m_write_msgs.front().toStdString().c_str(),
                                                     m_write_msgs.front().toStdString().length()),
                                 boost::bind(&StreamConnection::handleWrite, this,
                                             boost::asio::placeholders::error));
    }
}

void StreamConnection::handleWrite(const boost::system::error_code &error)
{
    if (!error)
    {
        m_write_msgs.pop_front();
        if (!m_write_msgs.empty())
        {
            boost::asio::async_write(m_socket,
                                     boost::asio::buffer(m_write_msgs.front().toStdString().c_str(),
                                                         m_write_msgs.front().toStdString().length()),
                                     boost::bind(&StreamConnection::handleWrite, this,
                                                 boost::asio::placeholders::error));
        }
    } else {
        onErrorOccured();
    }
}

void StreamConnection::stop()
{
    m_socket.close();
    m_write_msgs.clear();
}

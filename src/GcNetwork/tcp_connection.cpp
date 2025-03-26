#include "./GcNetwork/tcp_connection.h"
#include <sys/uio.h>

namespace gcnetwork{
    TcpConnection::~TcpConnection(){
        ::close(m_fd);
    }

    uint16_t TcpConnection::writeToBuffer(std::string & str){
        return m_buffer.append(str);
    }

    uint16_t TcpConnection::writeToBuffer(const char * str, uint16_t size){
        return m_buffer.append(str, size);
    }

    std::string TcpConnection::readFromBuffer(uint16_t size){
        return m_buffer.read(size);
    }

    std::string TcpConnection::readAllFromBuffer(){
        return m_buffer.read(m_buffer.readableBytes());
    }

    uint16_t TcpConnection::recvFromNetwork(){
        uint16_t ret = readv(m_fd, m_buffer.writevBegin(), 2);
        m_buffer.hasWritten(ret);
        return ret;
    }

    uint16_t TcpConnection::sendToNetwork(){
        uint16_t ret = writev(m_fd, m_buffer.readvBegin(), 2);
        m_buffer.hasRead(ret);
        return ret;
    }

    void TcpConnection::close(){
        ::close(m_fd);
    }

    uint16_t TcpConnection::readableBytes(){
        return m_buffer.readableBytes();
    }

    uint16_t TcpConnection::writableBytes(){
        return m_buffer.writableBytes();
    }
}
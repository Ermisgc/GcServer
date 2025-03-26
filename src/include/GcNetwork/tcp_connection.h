#pragma once
#include "net_base.h"
#include "./GcNetwork/buffer.h"
#include <string>

namespace gcnetwork{
    /**
     * @brief an concrete class for a connection.
     * @param addr the address of the connection, 16bytes.
     * @param m_buffer An instance of Buffer class, MAX_BUFFER_SIZE + 4bytes
     * @param m_fd the filedescriptor, 4bytes
     * @warning Because right now the TcpConnetion is a thread-unsafe class, 
     * the outer class should make sure that the TcpConnection is unique shared;
     */
    class TcpConnection{
        InetAddr addr;
        Buffer m_buffer; 
        int m_fd;
    public:
        TcpConnection() = delete;
        explicit TcpConnection(int fd, uint32_t _ip, uint16_t _port):m_fd(fd), addr(_ip, _port){}
        TcpConnection(int fd, const char * _ip, const char * _port):m_fd(fd), addr(_ip, _port){}
        TcpConnection(int fd, uint32_t _ip, const char * _port):m_fd(fd), addr(_ip, _port){}
        TcpConnection(int fd, const char * _ip, uint16_t _port):m_fd(fd), addr(_ip, _port){}
        TcpConnection(const TcpConnection & ) = delete;
        TcpConnection & operator=(const TcpConnection &) = delete;
        ~TcpConnection();

        /**
         * @brief get the ip of the connection
         * @return the ip of the connection as a uint32_t.
         */
        inline uint32_t ip(){return addr.ip();}

        /**
         * @brief get the ip of the connection
         * @return the ip of the connection as a std::string.
         */
        inline std::string ipString() {return addr.ipString();}

        /**
         * @brief get the port of the connection
         * @return the port of the connection as a uint16_t.
         */
        inline uint16_t port(){return addr.port();}

        /**
         * @brief get the port of the connection
         * @return the port of the connection as a std::string.
         */
        inline std::string portString(){return addr.portString();}

        /**
         * @brief get the file descriptor of the connection
         * @return the file descriptor
         */
        inline int fileDescriptor(){return fd();}

        /**
         * @brief get the file descriptor of the connection
         * @return the file descriptor
         */
        inline int fd() {return m_fd;}

        /**
         * @brief get the address of the connection
         * @return the address of the connection as a std::string
         */
        inline std::string ip_port(){ return "ip:" + ipString() + " port:" + portString();}

        /**
         * @brief write a string to the buffer
         * @param str the string to be written in.
         * @return the bytes that are successfully written in.
         */
        uint16_t writeToBuffer(std::string & str);

        /**
         * @brief write a const char *(string) to the buffer
         * @param str the const char * to be written in.
         * @param size the size of the str
         * @return the bytes that are successfully written in.
         */
        uint16_t writeToBuffer(const char * str, uint16_t size);

        /**
         * @brief read a string from the buffer
         * @param size the size of the string to be read.
         * @return the string that are successfully read.
         */
        std::string readFromBuffer(uint16_t size);

        /**
         * @brief read all the string from the buffer
         * @return the string that are successfully read.
         */
        std::string readAllFromBuffer();

        /**
         * @brief read from the network and write to the buffer
         * @return the bytes that are successfully read.
         */
        uint16_t recvFromNetwork();

        /**
         * @brief write the readable bytes to the network
         * @return the bytes that are successfully written.
         */
        uint16_t sendToNetwork();

        /**
         * @brief close the connection
         */
        void close();

        /**
         * @brief get the readable bytes from the buffer
         * @return the readable bytes.
         */
        uint16_t readableBytes();

        /**
         * @brief get the writable bytes from the buffer
         * @return the writable bytes.
         */
        uint16_t writableBytes();
    };

}
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
namespace gcnetwork{
    //stores net addr(been translate to big endian)
    //the integer parameter should be non-translated when creating
    typedef struct InetAddr{
        __uint32_t ip;
        __uint16_t port;
        InetAddr(int _ip, int _port):ip(htonl(_ip)), port(htons(_port)){}
        InetAddr(const char * _ip, const char * _port):ip(inet_addr(_ip)), port(htons(atoi(_port))){} 
        InetAddr(int _ip, const char * _port):ip(htonl(_ip)), port(htons(atoi(_port))){}
        InetAddr(const char * _ip, int _port):ip(inet_addr(_ip)), port(htons(_port)){}
    } InetAddr;
}
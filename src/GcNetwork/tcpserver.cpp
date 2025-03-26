#include "./GcNetwork/tcpserver.h"
#include "./GcHipe/dynamic_threadpool.h"
#include <iostream>
using namespace gcnetwork;
using namespace std;
#define BUF_SIZE 1024

void TcpServer::start(const char * ip, const char * port){
    int sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    InetAddr addr(ip, port);
    if(bind(sockfd, addr.addr(), addr.size()) == -1){
        //error handling
        exit(1);
    }

    cout << 1 << endl;

    if(listen(sockfd, 10) == -1){
        //error handling
        exit(1);
    }
    cout << 2 << endl;
    mr = std::make_shared<MainReactor>(sockfd, [](){std::cout << "new connection" << endl;});  //main thread
    mr->start();
}
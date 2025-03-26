#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include "./GcNetwork/tcpserver.h"

using namespace std;
using namespace gcnetwork;

int main(int argc, char ** argv){
    if(argc < 3) return 1;
    TcpServer ts;
    ts.start(argv[1], argv[2]);
    return 0;
}
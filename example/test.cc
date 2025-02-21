#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#define PORT 1214
#define BUF_SIZE 30

using namespace std;

void read_childproc(int sig){
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    cout << "remove proc: " << id << endl;
}

void error_handling(const char * msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char ** argv){
    if(argc != 2){
        cout << "use like this: test 1214" << endl;
        return -1;
    }

    int serverfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP), clientfd;
    sockaddr_in server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family = AF_INET;

    if(bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        error_handling("bind() error");
    }

    struct sigaction sga;
    sga.sa_flags = 0;
    sga.sa_handler = read_childproc;
    sigemptyset(&sga.sa_mask);
    sigaction(SIGCHLD, &sga, 0);

    if(listen(serverfd, 5) == -1){
        error_handling("listen() error");
    }

    while(1){
        socklen_t clientfd_size = sizeof(clientfd);
        clientfd = accept(serverfd, (struct sockaddr*)&client_addr, &clientfd_size);
        if(clientfd = -1) continue;
        else cout << "new client connected" << endl;

        pid_t pid = fork();
        if(pid == -1){ //resources are gone;
            close(clientfd);
            continue;
        } else if(pid == 0){  //child
            close(serverfd); //close the serverfd copied into the child process
            int str_len = 0;
            char buf[1024];
            while(str_len = read(clientfd, &buf, BUF_SIZE)){
                write(clientfd, &buf, str_len);
            }

            close(clientfd);
            cout << "client disconnected" << endl;
            return 0;
        } else { //father process
            close(clientfd);
        }
    }

    close(serverfd);
    return 0;
}
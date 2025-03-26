#include "./GcNetwork/main_reactor.h"
#include "./GcHipe/dynamic_threadpool.h"

using namespace gcnetwork;

MainReactor::MainReactor(int sockfd):server_fd(sockfd){
    isstop.store(false);
}

MainReactor::~MainReactor(){
    if (connection_callback) delete connection_callback;
    close();
}

void MainReactor::operator()(){
    this->start();
}

void MainReactor::start(){
    //here epoll is needed
    int epfd = epoll_create(1);
    struct epoll_event sock_event;
    sock_event.events = EPOLLIN;
    sock_event.data.fd = this->server_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, this->server_fd, &sock_event);

    while(!isstop.load()){
        struct epoll_event event_happened;
        int event_cnt = epoll_wait(epfd, &event_happened, 1, -1);
        if(event_cnt == -1){
            std::cout << "epoll_wait error with errno: " << errno << std::endl;
            break;
        } else if(event_cnt == 0){
            std::cout << "epoll_wait timeout" << std::endl;
            continue;
        }
        if(server_fd != event_happened.data.fd){
            std::cout << "overwhelmed error happened" << std::endl;
            break;
        }


        struct sockaddr_in addr;
        socklen_t siz = sizeof(addr);
        {
            //if(already closing, this will be locked until ::close(server_id), and then because isstop, this will break)
            std::unique_lock<std::mutex> locker(member_mtx);  
            if(isstop) break;
            int clientsock = accept(server_fd, (struct sockaddr *)&addr, &siz);
            if(connection_callback) connection_callback->fun();
            ::close(clientsock);
        }
    }
}

void MainReactor::close(){
    stop();
    {
        // if already accepting, this will be locked until finish accepting.
        std::unique_lock<std::mutex> locker(member_mtx);
        ::close(server_fd);
    }
}

void MainReactor::stop(){
    isstop.store(true);
}

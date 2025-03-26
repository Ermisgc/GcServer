#pragma once
#include <sys/socket.h>
#include <sys/epoll.h>
#include <condition_variable>
#include <atomic>
#include "net_base.h"
namespace gcnetwork{
    /**
     * @brief MainReactor is an epoll reactor for accepting new connections
     */
    class MainReactor{
    private:
        struct ConnectionCallback{
            virtual ~ConnectionCallback(){}
            virtual void fun() = 0;

        } * connection_callback;

        template<class _Callable>
        struct ConnectionCallbackImpl: public ConnectionCallback{
            _Callable foo;
            ConnectionCallbackImpl(_Callable && _clb):foo(std::forward<_Callable>(_clb)), ConnectionCallback(){}
            void fun() override{
                this->foo();
            }
        };

        int server_fd = 0;

        std::mutex member_mtx;
        std::condition_variable member_cv;

        std::atomic<bool> isstop;
    
    public:
        MainReactor() = delete;
        MainReactor(int sockfd);

        template<class _Callable>
        MainReactor(int sockfd, _Callable && _clb): server_fd(sockfd), \
            connection_callback(new ConnectionCallbackImpl<_Callable>(std::forward<_Callable>(_clb))){isstop.store(false);}

        ~MainReactor();

        //delete the copy and move constructor
        MainReactor(MainReactor & other) = delete;
        MainReactor(MainReactor && other) = delete;
        void operator=(MainReactor & other) = delete;
        void operator=(MainReactor && other) = delete;

        void operator()();

        void start();

        template<class _Callable>
        void setCustomConnectionCallback(_Callable && _clb){
            delete this->connection_callback;
            this->connection_callback = new ConnectionCallbackImpl<_Callable>(std::forward(_clb));
        }

        void stop();

    private:
        void close();
    };
}
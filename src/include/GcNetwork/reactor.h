#include <sys/socket.h>
#include <sys/epoll.h>
#include "net_base.h"
namespace gcnetwork{
    class MainReactor{
    private:

    public:
        MainReactor(const char * _ip);
        ~MainReactor();

        //delete the copy and move constructor
        MainReactor(MainReactor & other) = delete;
        MainReactor(MainReactor && other) = delete;
        void operator=(MainReactor & other) = delete;
        void operator=(MainReactor && other) = delete;

        void operator()();

        void start();

        void setCustomConnectionCallback();
    };
}
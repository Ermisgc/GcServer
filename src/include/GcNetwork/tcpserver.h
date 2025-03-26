#pragma once
#include "main_reactor.h"
#include "net_base.h"
#include "./GcHipe/dynamic_threadpool.h"

namespace gcnetwork{
    class TcpServer{
        std::shared_ptr<MainReactor> mr;
    public:
        TcpServer() = default;

        TcpServer(TcpServer & other) = delete;
        TcpServer(TcpServer && other) = delete;
        void operator=(TcpServer & other) = delete;
        void operator=(TcpServer && other) = delete;
        ~TcpServer() = default;

        void start(const char * ip, const char * port);

    };
}
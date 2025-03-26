#include "./GcSpdlog/logger.h"
#include "./GcHipe/dynamic_threadpool.h"
#include "iostream"
using namespace std;
using namespace gcspdlog;

int main(){
    gchipe::DynamicThreadPool * dtp = gchipe::DynamicThreadPool::getInstance(8);
    AsyncLogger al("logger", *dtp, GCSPDLOG_LEVEL_OFF, std::make_shared<FileSink>());
    int num = 10000;
    for(int i = 0;i < num; ++i){
        al.log(QuickMsgOFF("Logger" + std::to_string(i)));
    }
    return 0;
}
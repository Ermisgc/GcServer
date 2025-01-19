#include <iostream>
#include "./GcSpdlog/sink.h"
using namespace std;
using namespace gcspdlog;

int main(){
    cout << 1 << endl;
    FileSink::ptr sink = std::make_shared<FileSink>("log.txt");
    Sink::ptr sink1 = std::make_shared<Sink>();
    for(int i = 0;i < 10; ++i){
        LogMsg::ptr msg = std::make_shared<LogMsg>("Hello world", Level::GCSPDLOG_LEVEL_OFF, SourceLoc(__FILE__, __func__, __LINE__));
        cout << i << endl;
        sink->log(msg);
        sink1->log(msg);
    }
    return 0;
}
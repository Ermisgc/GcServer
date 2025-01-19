#include <iostream>
#include "formatter.h"
using namespace std;
using namespace gcspdlog;
int main(){
    LogMsg::ptr msg = std::make_shared<LogMsg>("Hello world", Level::GCSPDLOG_LEVEL_OFF, SourceLoc(__FILE__, __func__, __LINE__));
    Formatter::ptr fmt = std::make_shared<Formatter>("[%l][%y-%m-%d-%h-%i-%e][%o,line:%n]: %s");
    cout << fmt->format(msg);
    return 0;
}
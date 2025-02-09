#include <iostream>
//#include "./GcSpdlog/sink.h"
#include "./GcHipe/dynamic_threadpool.h"
using namespace std;
using namespace gchipe;

int add(int a, int b){
    return a + b;
}

int main(){
    DynamicThreadPool * dtp = new DynamicThreadPool(4);
    for(int i = 0;i < 2000; ++i){
        auto ret = dtp->submit(std::bind(add, i, i));
        cout << ret.get() << endl;
    }
    dtp->close();
    return 0;
}
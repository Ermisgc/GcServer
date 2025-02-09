#include <coroutine>
#include <iostream>
using namespace std;
struct CoRet{
    struct promise_type{  //协程的返回值一定要一个promise_type
        suspend_never initial_suspend() {return {};}
        suspend_never final_suspend() noexcept {return {};}
        void unhandled_exception() {}
        CoRet get_return_object(){
            return {coroutine_handle<promise_type>::from_promise(*this)};
        }
    };

    coroutine_handle<promise_type> _h;  //handle可以resume:_h.resume() 或 _h();
};

struct Input{
    bool await_ready() {return false;};  //当我们遇到co_await是否需要暂停并跳转，false就是需要
    void await_suspend(coroutine_handle<CoRet::promise_type> h){  //跳转回main函数或handle协程
        //h.promise()
    }
    int await_resume() {return 0;};
};

CoRet Guess(){
    // CoRet::promise_type promise;
    // CoRet ret = promise.get_return_object();
    // co_await promise.initial_suspend();
    Input input;
    int g = co_await input;
    cout << "coroutime: you guess" << g << endl;

    // co_await promise.final_suspend();
}

int main(){
    auto ret = Guess();
    cout << "main: make a guess ..." << endl; 

    ret._h.resume();
}
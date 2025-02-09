#include "./GcHipe/dynamic_threadpool.h"
#include <iostream>
namespace gchipe{
    //the initial number of thread;
    DynamicThreadPool::DynamicThreadPool(unsigned int th_num){
        for(int i = 0;i < th_num; ++i){
            threads.emplace_back(std::thread(&DynamicThreadPool::worker, this, i));
        }
    }

    void DynamicThreadPool::waitforAllTasks(){
        waiting.store(true);
        

        waiting.store(false);
    }

    void DynamicThreadPool::waitforCurrentTasks(){
        for(auto & thread: threads){
            thread.join();
        }
    }

    void DynamicThreadPool::setTaskOverflow(std::function<void(void)> & _overflow_fun){
        this->overflow_fun = _overflow_fun;
    }

    void DynamicThreadPool::worker(int index){
        while(!stop){
            std::unique_lock<std::mutex> locker(shared_lock);
            //awake if tasks are not empty or we try to stop this threadpool
            wait_cv.wait(locker, [this]()->bool{ return !tasks.empty() || stop;});

            //awake when user try to stop
            if(stop) break;

            HipeTask task = std::move(tasks.front());
            tasks.pop();
            gchipe::invoke(task);
        }
    }

    void DynamicThreadPool::setMaxTaskNum(uint32_t num){
        this->max_task_num = num;
    }

    void DynamicThreadPool::close(){
        this->stop.store(true);
        wait_cv.notify_all();
        waitforCurrentTasks();
    }
}
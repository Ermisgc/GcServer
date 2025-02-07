#include "./GcHipe/dynamic_threadpool.h"
#include <iostream>
namespace gchipe{
    //the initial number of thread;
    DynamicThreadPool::DynamicThreadPool(unsigned int th_num){
        for(int i = 0;i < th_num; ++i){
            threads.emplace_back(std::thread(&DynamicThreadPool::worker, this, i));
        }
    }

    template<class _Callable>
    auto DynamicThreadPool::submit(_Callable && task) -> std::future<std::invoke_result_t<decltype(task)>>{
        using RT = std::invoke_result_t<decltype(task)>;
        if(waiting.load()){
            std::cout << "The thread pool is waiting for the rest tasks, you can not add more tasks" << std::endl;
            return std::future<RT>();
        }
        std::packaged_task<RT()> pt(std::move(task));  //only rvalue is needed
        std::future<RT> ret = pt.get_future();
        {
            std::unique_lock<std::mutex> locker(shared_lock);
            if(tasks.size() >= max_task_num){
                std::cout << "Task queue overflow" << std::endl;
                return std::future<RT>;
            }         
            //there: task has been std::bind, so the task is a function<RT()>
            tasks.emplace(std::move(pt));
        }
        wait_cv.notify_one();
        return ret;
    }

    template<class _Callable>
    void DynamicThreadPool::execute(_Callable && task){
        if(waiting.load()){
            std::cout << "The thread pool is waiting for the rest tasks, you can not add more tasks" << std::endl;
            return;
        }
        {
            std::unique_lock<std::mutex> locker(shared_lock);
            if(tasks.size() >= max_task_num){
                std::cout << "Task queue overflow" << std::endl;
                return;
            }
            tasks.emplace_back(HipeTask(std::forward<_Callable>(task)));
        }
        wait_cv.notify_one();
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
    }
}
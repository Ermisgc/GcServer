#include <atomic>
#include <list>
#include <queue>
#include <thread>
#include <functional>
#include <condition_variable>
#include "./GcHipe/hipe_task.h"

namespace gchipe{
    class DynamicThreadPool{
    private:
        uint32_t max_task_num{1000};
        std::atomic<int> total_tasks{0};
        std::atomic<int> total_load{0};  
        std::queue<HipeTask> tasks;
         
        std::condition_variable wait_cv;
        std::list<std::thread> threads;     
        std::mutex shared_lock;

        std::function<void(void)> overflow_fun;
        std::atomic<bool> stop{false};
        std::atomic<bool> waiting{false};

    public:
        DynamicThreadPool() = delete;
        
        //the initial number of thread;
        DynamicThreadPool(unsigned int th_num = 1);

        template<class _Callable>
        auto submit(_Callable &&task) -> std::future<std::invoke_result_t<decltype(task)>>;
        
        template<class _Callable>
        void execute(_Callable &&task);

        void waitforAllTasks();

        void waitforCurrentTasks();

        void close();

        void setTaskOverflow(std::function<void(void)> & _overflow_fun);

        void setMaxTaskNum(uint32_t num);

    private:
        //work function
        void worker(int index);
    }

}
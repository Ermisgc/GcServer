#include <atomic>
#include "./GcHipe/hipe_task.h"

namespace gchipe{
    class DynamicThreadPool{
    private:
        std::atomic<int> total_tasks;
        std::queue<HipeTask>




    }

}
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include "./GcHipe/dynamic_threadpool.h"

using namespace std;
using namespace gchipe;

// 简单的任务函数，模拟计算密集型任务
void computeTask(int id) {
    // unsigned int result = 0;
    // for (int i = 0; i < 1000000; ++i) {
    //     result += i;
    // }
    // // 可选：输出任务结果
    // cout << "Task " << id << " result: " << result << endl;
}

// 任务类型
uint vec_size = 4096;
uint vec_nums = 2048;
std::vector<std::vector<double>> results(vec_nums, std::vector<double>(vec_size));

// computation intensive task(计算密集型任务)
void computation_intensive_task() {
    for (int i = 0; i < vec_nums; ++i) {
        for (size_t j = 0; j < vec_size; ++j) {
            results[i][j] = std::log(std::sqrt(std::exp(std::sin(i) + std::cos(j))));
        }
    }
}

int main(int argc, char ** argv) {
    int numTasks = atoi(argv[1]);

    // 创建一个动态线程池，初始线程数为 4
    DynamicThreadPool * pool = DynamicThreadPool::getInstance(8);
    //pool.setMaxTaskNum(100000);

    // 测试线程池性能
    auto start = chrono::high_resolution_clock::now();

    // 提交 10000 个任务
    for (int i = 0; i < numTasks; ++i) {
        pool->execute(computation_intensive_task);
    }

    // 等待所有任务完成
    pool->waitforAllTasks();

    auto end = chrono::high_resolution_clock::now();

    // 计算并输出用时
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Processed " << numTasks << " tasks in " << duration << " ms." << endl;
    cout << "Per task: " << duration / numTasks << " ms"<< endl;
    return 0;
}
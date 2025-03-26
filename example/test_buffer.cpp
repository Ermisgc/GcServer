#include "./GcNetwork/buffer.h"
#include <iostream>
#include <chrono>
#include <string>
#include <cassert>

using namespace gcnetwork;
using namespace std;
using namespace std::chrono;

// 基本功能测试
void test_basic_operations() {
    Buffer buf;
    
    // 测试空缓冲区
    assert(buf.readableBytes() == 0);
    assert(buf.writableBytes() == MAX_BUFFER_SIZE - 1);

    // 写入测试
    string test_str = "Hello, Buffer!";
    uint16_t written = buf.append(test_str);
    assert(written == test_str.length());
    assert(buf.readableBytes() == test_str.length());

    // 读取测试
    string result = buf.read(test_str.length());
    assert(result == test_str);
    assert(buf.readableBytes() == 0);
    
    cout << "[+]Basic operations test passed!" << endl;
}

// 边界条件测试
void test_boundary_conditions() {
    Buffer buf;
    const int MAX_SIZE = MAX_BUFFER_SIZE - 1; // 可用空间
    
    // 填满缓冲区
    string full_data(MAX_SIZE, 'A');
    uint16_t written = buf.append(full_data.c_str(), MAX_SIZE);
    assert(written == MAX_SIZE);
    assert(buf.writableBytes() == 0);

    // 测试读取后空间释放
    string read_data = buf.read(MAX_SIZE/2);
    assert(read_data.length() == MAX_SIZE/2);
    assert(buf.writableBytes() == MAX_SIZE/2);

    // 测试环形覆盖
    // string new_data(MAX_SIZE/2 + 10, 'B');
    // written = buf.append(new_data);
    // assert(written == MAX_SIZE/2 + 10);
    // assert(buf.readableBytes() == MAX_SIZE/2 + 10);

    cout << "[+]Boundary conditions test passed!" << endl;
}

// 性能测试
void test_performance() {
    Buffer buf;
    const int TOTAL_SIZE = 1000000; // 1MB数据
    const int CHUNK_SIZE = 512;     // 每次写入1KB
    const int LOOPS = TOTAL_SIZE / CHUNK_SIZE;

    string test_data(CHUNK_SIZE, 'X');

    // 写入性能测试
    auto start_write = high_resolution_clock::now();
    for (int i = 0; i < LOOPS; ++i) {
        buf.append(test_data);
        buf.read(CHUNK_SIZE); // 模拟读写交替
    }
    auto duration_write = duration_cast<milliseconds>(high_resolution_clock::now() - start_write);

    // 读取性能测试
    auto start_read = high_resolution_clock::now();
    for (int i = 0; i < LOOPS; ++i) {
        buf.append(test_data);
        string data = buf.read(CHUNK_SIZE);
    }
    auto duration_read = duration_cast<milliseconds>(high_resolution_clock::now() - start_read);

    cout << "[+]Performance test results:\n"
         << "Write throughput: " << (TOTAL_SIZE/1024) / (duration_write.count()/1000.0) << " MB/s\n"
         << "Read throughput: " << (TOTAL_SIZE/1024) / (duration_read.count()/1000.0) << " MB/s\n";
}

int main() {
    try {
        test_basic_operations();
        test_boundary_conditions();
        test_performance();
        cout << "All tests passed successfully!" << endl;
    } catch (const exception& e) {
        cerr << "Test failed: " << e.what() << endl;
        return 1;
    }
    return 0;
}
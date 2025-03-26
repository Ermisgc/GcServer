#include "./GcNetwork/tcp_connection.h"
#include <assert.h>
using namespace gcnetwork;

#define EXPECT_EQ(a, b) assert(a == b)
#define TEST(test_class, test_name) \
    void test_class##_##test_name()

TEST(TcpConnectionTest, Constructor) {
    // 创建 TcpConnection 对象并验证属性
    TcpConnection connection(1, "127.0.0.1", "8080");
    EXPECT_EQ(connection.ip(), 0x7F000001);
    EXPECT_EQ(connection.port(), 8080);
    EXPECT_EQ(connection.fd(), 1);
}

TEST(TcpConnectionTest, WriteToBuffer) {
    TcpConnection connection(1, "127.0.0.1", "8080");
    std::string str = "Test data";
    uint16_t written = connection.writeToBuffer(str);
    EXPECT_EQ(written, str.size());
}

TEST(TcpConnectionTest, ReadFromBuffer) {
    TcpConnection connection(1, "127.0.0.1", "8080");
    std::string str = "Test data";
    connection.writeToBuffer(str);
    std::string readStr = connection.readFromBuffer(str.size());
    EXPECT_EQ(readStr, str);
}

TEST(TcpConnectionTest, ReadAllFromBuffer) {
    TcpConnection connection(1, "127.0.0.1", "8080");
    std::string str = "Test data";
    connection.writeToBuffer(str);
    std::string readAllStr = connection.readAllFromBuffer();
    EXPECT_EQ(readAllStr, str);
}

TEST(TcpConnectionTest, RecvFromNetwork) {
    // 模拟从网络接收数据并验证
}

TEST(TcpConnectionTest, SendToNetwork) {
    // 模拟向网络发送数据并验证
}

TEST(TcpConnectionTest, Close) {
    TcpConnection connection(1, "127.0.0.1", "8080");
    connection.close();
    // 验证连接已关闭
}

TEST(TcpConnectionTest, ReadableBytes) {
    TcpConnection connection(1, "127.0.0.1", "8080");
    std::string str = "Test data";
    connection.writeToBuffer(str);
    uint16_t readable = connection.readableBytes();
    EXPECT_EQ(readable, str.size());
}

TEST(TcpConnectionTest, WritableBytes) {
    TcpConnection connection(1, "127.0.0.1", "8080");
    uint16_t writable = connection.writableBytes();
    // 验证可写字节数
}

int main(){
    TcpConnectionTest_Close();
    TcpConnectionTest_Constructor();
    TcpConnectionTest_ReadAllFromBuffer();
    TcpConnectionTest_ReadFromBuffer();
    TcpConnectionTest_ReadableBytes();
    TcpConnectionTest_RecvFromNetwork();
    TcpConnectionTest_SendToNetwork();
    TcpConnectionTest_WritableBytes();
    TcpConnectionTest_WriteToBuffer();
    return 0;
}
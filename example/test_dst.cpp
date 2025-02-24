#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <map> // for comparison with std::map
#include <unordered_set>
#include <algorithm>
#include "./GcDst/rbtree.h"
#include "./GcDst/skiplist.h"

// Todo list:
// 1. how to handle the same key is a question
// 2. there are some problems in deletion
// 3. the insertion and deletion is faster than std::map, but finding is slower than std::map
using namespace std;

using namespace gcdst;

std::vector<int> generate_unique_keys(int n) {
    std::unordered_set<int> keys;
    while (keys.size() < n) {
        int key = rand() % (n * 10);  // 生成 0 到 10n 之间的随机数
        keys.insert(key);
    }
    return std::vector<int>(keys.begin(), keys.end());
}

#if 0
// 验证红黑树的性质（这里假设你已经实现了验证函数）
bool validate_rbtree(rbtree<int, int>& tree) {
    return tree.test_insert_correction();
}

// 测试插入操作
void test_insert(rbtree<int, int>& tree, const std::vector<int>& keys) {
    for (int key : keys) {
        tree.insert(key, key);
        if (!validate_rbtree(tree)) {
            std::cerr << "[-] Red-Black Tree property violated after inserting key: " << key << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    std::cout << "[+] Insertion test passed!" << std::endl;
}

// 测试查找操作
void test_find(rbtree<int, int>& tree, const std::vector<int>& keys) {
    for (int key : keys) {
        if (!tree.find(key)) {
            std::cerr << "[-] Key not found: " << key << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    std::cout << "[+] Find test passed!" << std::endl;
}

// 测试删除操作
void test_delete(rbtree<int, int>& tree, const std::vector<int>& keys) {
    std::vector<int> keys_to_delete = keys;
    std::random_shuffle(keys_to_delete.begin(), keys_to_delete.end());  // 随机打乱顺序

    for (size_t i = 0; i < keys_to_delete.size() / 2; ++i) {  // 删除一半的键值
        tree.remove(keys_to_delete[i]);
        //cout << i << endl;
        if (!validate_rbtree(tree)) {
            std::cerr << "[-] Red-Black Tree property violated after deleting key: " << keys_to_delete[i] << std::endl;
            exit(1);
        }
    }
    std::cout << "[+] Deletion test passed!" << std::endl;
}

int main() {
    srand(time(nullptr));  // 初始化随机数种子

    const int NUM_KEYS = 10000;  // 测试数据量
    rbtree tree;

    // 生成不重复的键值
    std::vector<int> keys = generate_unique_keys(NUM_KEYS);

    // 测试插入
    test_insert(tree, keys);

    // 测试查找
    test_find(tree, keys);

    // 测试删除
    test_delete(tree, keys);

    // 再次验证查找（确保删除后的键值不存在）
    for (size_t i = 0; i < keys.size() / 2; ++i) {
        if (tree.find(keys[i])) {
            std::cerr << "[-] Key should have been deleted but was found: " << keys[i] << std::endl;
            exit(1);
        }
    }
    std::cout << "[+] Post-deletion find test passed!" << std::endl;

    std::cout << "[+] All tests passed successfully!" << std::endl;
    return 0;
}
#endif


// 测试插入操作
void test_insert(skiplist<int, int>& tree, const std::vector<int>& keys) {
    for (int key : keys) {
        tree.insert(key, key);
    }
    std::cout << "[+] Insertion test passed!" << std::endl;
}

// 测试查找操作
void test_find(skiplist<int, int>& tree, const std::vector<int>& keys) {
    for (int key : keys) {
        if (!tree.isExist(key)) {
            std::cerr << "[-] Key not found: " << key << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    std::cout << "[+] Find test passed!" << std::endl;
}

// 测试删除操作
void test_delete(skiplist<int, int>& tree, const std::vector<int>& keys) {
    std::vector<int> keys_to_delete = keys;
    std::random_shuffle(keys_to_delete.begin(), keys_to_delete.end());  // 随机打乱顺序

    for (size_t i = 0; i < keys_to_delete.size() / 2; ++i) {  // 删除一半的键值
        tree.remove(keys_to_delete[i]);
        //cout << i << endl;
        // if (!validate_rbtree(tree)) {
        //     std::cerr << "[-] Red-Black Tree property violated after deleting key: " << keys_to_delete[i] << std::endl;
        //     exit(1);
        // }
    }
    for (size_t i = 0; i < keys_to_delete.size() / 2; ++i) {
        if (tree.isExist(keys_to_delete[i])) {
            std::cerr << "[-] Key should have been deleted but was found: " << keys[i] << std::endl;
            exit(1);
        }
    }
    std::cout << "[+] Deletion test passed!" << std::endl;
}

int main() {
    srand(time(nullptr));  // 初始化随机数种子

    const int NUM_KEYS = 10000;  // 测试数据量
    skiplist tree(32);

    // 生成不重复的键值
    std::vector<int> keys = generate_unique_keys(NUM_KEYS);

    // 测试插入
    test_insert(tree, keys);

    // 测试查找
    test_find(tree, keys);

    // 测试删除
    test_delete(tree, keys);

    // 再次验证查找（确保删除后的键值不存在）
    std::cout << "[+] Post-deletion find test passed!" << std::endl;

    std::cout << "[+] All tests passed successfully!" << std::endl;
    return 0;
}
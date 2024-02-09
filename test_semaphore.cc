#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

std::counting_semaphore<5> sem(5);

void worker() {
    sem.acquire();  // 获取信号量资源
    // 访问共享资源
    std::cout << "Worker is accessing the shared resource." << std::endl;
    sem.release();  // 释放信号量资源
}

int main() {
    uint64_t thread_num;
    std::vector<std::jthread> threads;

    return 0;
}
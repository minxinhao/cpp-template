#include <iostream>
#include <atomic>
int main() {
    std::atomic<int> n = 6;
    std::atomic<int> m(6);

    std::cout << n << '\n';
}
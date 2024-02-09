#include <iostream>
#include <thread>
#include <syncstream>

void printThreadId(std::ostream& os) {
    std::osyncstream synchronized_os(os);
    synchronized_os << "Thread ID: " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::cout << "Main Thread ID: " << std::this_thread::get_id() << std::endl;

    std::thread t1(printThreadId, std::ref(std::cout));
    std::thread t2(printThreadId, std::ref(std::cout));

    t1.join();
    t2.join();

    return 0;
}
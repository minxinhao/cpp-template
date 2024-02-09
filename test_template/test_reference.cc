#include "dbg.h"
#include <iostream>
#include <utility>

void process(int &x)
{
    std::cout << "Lvalue reference: " << x << std::endl;
}

void process(int &&x)
{
    std::cout << "Rvalue reference: " << x << std::endl;
}

template <typename T> void forwardAndProcess(T &&arg)
{
    int a = 1;
    T tmp = std::forward<T>(arg);
    dbg(tmp);
    process(std::forward<T>(arg));
}

void func(int &x)
{
    dbg(x);
    x++;
}
void func(int &&x)
{
    dbg(x);
}
int main()
{
    int a = 10;
    int& b = a;
    int&& c = std::move(a);

    forwardAndProcess(a);            // Lvalue reference
    forwardAndProcess(std::move(a)); // Rvalue reference
    forwardAndProcess(c); // Rvalue reference
    forwardAndProcess(std::forward<int>(c)); // Rvalue reference
    forwardAndProcess(std::forward<int&>(c)); // Rvalue reference
    // forwardAndProcess(std::forward<int&>(std::move(a))); // Error
    forwardAndProcess(std::forward<int>(std::move(a))); // Error

    func(a);
    func(b);
    func(a);
    func(std::move(a));
    func(c);
    func(std::forward<int>(c));
    func(std::forward<int&>(c));
    func(std::forward<int>(a));
    func(std::forward<int&>(a));
    return 0;
}
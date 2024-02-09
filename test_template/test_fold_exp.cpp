#include <iostream>
#include <string>
#include <vector>

template <typename... Args> auto sum(Args... args)
{
    return (args + ...);
}

template <typename... Args> std::string concatenate(Args... args)
{
    return (std::to_string(args) + ...);
}


template <typename... Args> void callFunctions(Args... args)
{
    (...,args());
}

void func1()
{
    std::cout << "Function 1 called" << std::endl;
}

void func2()
{
    std::cout << "Function 2 called" << std::endl;
}

void func3()
{
    std::cout << "Function 3 called" << std::endl;
}

// 输出：
// Function 1 called
// Function 2 called
// Function 3 called

template <typename... Args> auto createVector(Args... args)
{
    return std::vector<int>{args...};
}

std::vector<int> vec = createVector(1, 2, 3, 4, 5); // 结果为 {1, 2, 3, 4, 5}

int main()
{

    {
        int result = sum(1, 2, 3, 4, 5); // 结果为15
    }
    std::string result = concatenate(1, 2, 3, 4, 5); // 结果为"12345"
    callFunctions(func1, func2, func3);
    return 0;
}
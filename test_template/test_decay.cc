#include <iostream>
#include <type_traits>

template <typename T>
void printType()
{
    std::cout << "Original type: " << typeid(T).name() << std::endl;
    std::cout << "Decayed type: " << typeid(std::decay_t<T>).name() << std::endl;
    std::cout << std::endl;
}

int main()
{
    // 示例1：非引用类型保持不变
    printType<int>();  // Original type: int, Decayed type: int

    // 示例2：左值引用衰减为非引用类型
    printType<int&>();  // Original type: int&, Decayed type: int

    // 示例3：右值引用衰减为非引用类型
    printType<int&&>();  // Original type: int&&, Decayed type: int

    // 示例4：保留const限定符
    printType<const int>();  // Original type: const int, Decayed type: const int

    // 示例5：数组类型转换为指针类型
    printType<int[5]>();  // Original type: int [5], Decayed type: int*

    return 0;
}


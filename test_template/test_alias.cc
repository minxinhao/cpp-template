#include <iostream>

template <typename T> class MyTemplateClass
{
  public:
    void Print(T value)
    {
        std::cout << "Value: " << value << std::endl;
    }
};

template <typename T> using MyAlias = MyTemplateClass<T>;

template <typename T, typename... Args> class MyPrint
{
  public:
    MyPrint(T value, Args... args)
    {
        std::cout << "Value: ";
        ((std::cout << args << " "), ...);
        std::cout << std::endl;
    }
};

template <typename T, typename... Args> using Printer = MyPrint<T, Args...>;

int main()
{
    MyAlias<int> obj; // 使用别名创建对象
    obj.Print(42);    // 调用对象的成员函数
    MyPrint obj2(2, "hello", " ", "world", "!");
    // Printer obj3(2, "hello", " ", "world", "!"); // 没办法做到自动推导
    Printer<int, const char*, const char*, const char*, const char*> obj3(3, "hello", " ", "world", "!");
    return 0;
}
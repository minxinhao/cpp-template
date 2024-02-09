#include <iostream>

template <typename F, typename... Args> auto func_forwad(F func, Args... args) -> decltype(func(args...))
{
    return func(args...);
}

void print()
{
    std::cout << "hello"
              << "\n";
}

void print_str(const char *str)
{
    std::cout << str << "\n";
}

void print_header(int num, char c)
{
    for (int i = 0; i < num; i++)
    {
        std::cout << c;
    }
    std::cout << "\n";
}

int calculate()
{
    return 10;
}

int main()
{
    func_forwad(print);
    func_forwad(print_str, "mxh");
    func_forwad(print_header, 10, '-');
    func_forwad(print_str, "start");
    func_forwad(print_header,func_forwad(calculate),'*');
}
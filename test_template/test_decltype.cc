#include "dbg.h"
#include <iostream>
#include <type_traits>

template <typename T> void print_type()
{
    if (!std::is_reference_v<T>)
        dbg("PlainType");
    if (std::is_lvalue_reference_v<T>)
        dbg("LValueReference");
    if (std::is_rvalue_reference_v<T>)
        dbg("RValueReference");
}

void func1(auto &&para)
{
    dbg("decltype para");
    print_type<decltype(para)>();
    dbg("forward<para>");
    print_type<decltype(std::forward<decltype(para)>(para))>();
}

template <typename Args> void func2(Args &&args)
{
    dbg("args");
    print_type<Args>();
    dbg("forward<args>");
    print_type<decltype(std::forward<Args>(args))>();
}

int main()
{
    int source_type = 0;
    int &l_reference = source_type;
    int &&r_reference = std::move(source_type);

    func1(1);
    func1(source_type);
    func1(l_reference);
    func1(r_reference);
    func1(std::move(source_type));

    func2(1);
    func2(source_type);
    func2(l_reference);
    func2(r_reference);
    func2(std::move(source_type));
}
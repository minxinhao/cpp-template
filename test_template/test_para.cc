#include "dbg.h"
#include <iostream>

template <typename T> void func(T t)
{
    if (!std::is_reference_v<T>)
        dbg("PlainType");
    if (std::is_lvalue_reference_v<T>)
        dbg("LValueReference");
    if (std::is_rvalue_reference_v<T>)
        dbg("RValueReference");
}

template <typename T> void func2(T &&t)
{
    if (!std::is_reference_v<T>)
        dbg("PlainType");
    if (std::is_lvalue_reference_v<T>)
        dbg("LValueReference");
    if (std::is_rvalue_reference_v<T>)
        dbg("RValueReference");
}

struct Test
{
    Test()
    {
        dbg("construct");
    }
    Test(const Test &)
    {
        dbg("copy");
    }
    Test(Test &&)
    {
        dbg("move");
    }
    void operator()()
    {
        dbg("test");
    }
};

int main()
{

    Test t;
    Test &tt = t;
    Test &&r_tt = std::move(t);

    func(t);      // copy + PlainType
    func(tt);     // copy + PlainType
    func(r_tt);   // copy + PlainType
    func(Test()); // constructs + PlainType

    func2(t);      // LValueReference
    func2(tt);     // LValueReference
    func2(r_tt);   // LValueReference
    func2(Test()); // constructs + PlainType
}
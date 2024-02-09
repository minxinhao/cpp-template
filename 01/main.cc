#include "dbg.h"
#include <iostream>
template <typename T, typename F> T operator|(T &&t, F &&f)
{
    for (auto &i : t)
        f(i);
    return t;
}

int main()
{
    std::vector v{1, 2, 3};
    std::function f{[](const int &i) { dbg(i); }};
    auto f2 = [](int &i) { i *= i; };
    v | f2 | f;
}
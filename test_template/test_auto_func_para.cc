#include "dbg.h"
#include <functional>
#include <iostream>
#include <optional>
#include <type_traits>

void print(auto &&func, auto &&...args)
{
    if constexpr (std::is_same_v<std::invoke_result_t<decltype(func), decltype(args)...>, void>)
    {
    }
    else
    {
        auto res = func(std::forward<decltype(args)>(args)...);
        std::cout << res << "\n";
    }
}

int main()
{
    auto nothing = []() { return; };
    auto one = []() { return 1; };
    auto cal = [](auto &&x, auto &&y)
        requires requires(decltype(x) a, decltype(y) b) { a + b; }
    { return x + y; };
    print(nothing);
    print(one);
}
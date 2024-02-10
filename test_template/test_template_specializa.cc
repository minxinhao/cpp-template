#include <functional>
#include <iostream>
#include <type_traits>

template <typename Func, typename... Args>
    requires(std::is_void_v<std::invoke_result_t<Func, Args...>>)
void print_forward(Func &&func, Args &&...args)
{
    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
}

template <typename Func, typename... Args>
    requires(!std::is_void_v<std::invoke_result_t<Func, Args...>>)
void print_forward(Func &&func, Args &&...args)
{
    auto res = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    std::cout << res << "\n";
}

int main()
{
    auto nothing = []() { return; };
    auto one = []() { return 1; };
    auto cal = [](auto &&x, auto &&y)
        requires requires(decltype(x) a, decltype(y) b) { a + b; }
    { return x + y; };
    print_forward(nothing);
    print_forward(one);

    return 0;
}
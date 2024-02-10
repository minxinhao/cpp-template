#include <iostream>
#include <functional>
#include <type_traits>
#include <utility>

// 转发函数模板
template <typename Func, typename... Args>
auto forward_call(Func&& func, Args&&... args)
{
    if constexpr (std::is_same_v<std::invoke_result_t<Func, Args...>, void>)
    {
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    }
    else
    {
        return std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    }
}

// 示例函数
void foo(int x)
{
    std::cout << "foo: " << x << std::endl;
}

int bar(int x, int y)
{
    std::cout << "bar: " << x << ", " << y << std::endl;
    return x + y;
}

int main()
{
    forward_call(foo, 42);
    int result = forward_call(bar, 10, 20);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
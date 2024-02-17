#include "dbg.h"
#include <initializer_list>
#include <stdint.h>

template <class Ty, size_t size> struct array
{
    Ty *begin()
    {
        return arr;
    };
    Ty *end()
    {
        return arr + size;
    };
    Ty arr[size];
};

template <class Ty, class... Args>
    requires(std::same_as<Ty, Args> && ...) // 不会这个C++20约束以及里面折叠表达的用法也可以不用
array(Ty, Args...) -> array<Ty, 1 + sizeof...(Args)>;

int main()
{
    ::array arr{1, 2, 3, 4, 5};
    for (const auto &i : arr)
    {
        std::cout << i << ' ';
    }
}
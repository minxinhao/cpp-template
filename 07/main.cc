#include <iostream>
#include <type_traits>

struct init {
    template <typename T>
    operator T(); // 无定义 我们需要一个可以转换为任何类型的在以下特殊语境中使用的辅助类
};

template <typename T>
consteval size_t size(auto&&...Args) {
    if constexpr (!requires{T{ Args... }; }) {
        return sizeof...(Args) - 1;
    }
    else {
        return size<T>(Args..., init{});
    }
}

template <typename T, typename F>
void for_each_member(T const& v, F&& f) {
    static_assert(std::is_aggregate_v<T>);//检测是否为聚合类型

    if constexpr (size<T>() == 4u) {//使用C++17的编译期if和结构化绑定来遍历
        const auto& [m0, m1, m2, m3] = v;
        f(m0); f(m1); f(m2); f(m3);
    }
    else if constexpr (size<T>() == 3u) {
        const auto& [m0, m1, m2] = v;
        f(m0); f(m1); f(m2);
    }
    else if constexpr (size<T>() == 2u) {
        const auto& [m0, m1] = v;
        f(m0); f(m1);
    }
    else if constexpr (size<T>() == 1u) {
        const auto& [m0] = v;
        f(m0);
    }
}

int main() {
    struct X { std::string s{ " " }; }x;
    struct Y { double a{}, b{}, c{}, d{}; }y;
    std::cout << size<X>() << '\n';
    std::cout << size<Y>() << '\n';

    auto print = [](const auto& member) {
        std::cout << member << ' ';
    };
    for_each_member(x, print);
    for_each_member(y, print);
}
#include <iostream>
#include <tuple>
#include "dbg.h"

template <std::size_t... Is, typename F, typename T> auto map_filter_tuple(F f, T &t)
{
    return std::make_tuple(f(std::get<Is>(t))...);
}

template <std::size_t... Is, typename F, typename T> auto map_filter_tuple(std::index_sequence<Is...>, F f, T &t)
{
    return std::make_tuple(f(std::get<Is>(t))...);
}

template <typename S, typename F, typename T> auto map_filter_tuple(F &&f, T &t)
{
    return map_filter_tuple(S{}, std::forward<F>(f), t);
}

template<typename T> 
T add_one(T t){
    return t+static_cast<T>(1);
}

int main()
{
    // std::tuple<int, double, std::string> t(42, 3.14, "Hello");
    std::tuple<int, double, float> t(42, 3.14, 1.0f);

    auto mapped_tuple = map_filter_tuple<std::index_sequence<0, 1,2>>([](auto x) { return x + 1; }, t);
    dbg(mapped_tuple);
    std::cout << std::get<0>(mapped_tuple) << std::endl; // Output: 43
    std::cout << std::get<1>(mapped_tuple) << std::endl; // Error: Index out of range

    return 0;
}
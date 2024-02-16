#include "dbg.h"
#include <cassert>
#include <cstdio>

#include <functional>
#include <iostream>
#include <stdexcept>

struct scope_guard_1
{
    std::function<void()> f;
    template <typename Func, typename... Args>
        requires std::invocable<Func, std::unwrap_reference_t<Args>...>
    scope_guard_1(Func &&func, Args &&...args)
        : f{[func = std::forward<Func>(func), ... args = std::forward<Args>(args)]() mutable {
              std::invoke(std::forward<std::decay_t<Func>>(func),
                          std::unwrap_reference_t<Args>(std::forward<Args>(args))...);
          }}
    {
    }
    ~scope_guard_1()
    {
        f();
    }
    scope_guard_1(const scope_guard_1 &) = delete;
    scope_guard_1 &operator=(const scope_guard_1 &) = delete;
};

template <typename F, typename... Args>
    requires requires(F f, Args... args) { std::invoke(f, args...); }
struct scope_guard_2
{
    F f;
    std::tuple<Args...> values;

    template <typename Fn, typename... Ts>
    scope_guard_2(Fn &&func, Ts &&...args) : f{std::forward<Fn>(func)}, values{std::forward<Ts>(args)...}
    {
    }
    ~scope_guard_2()
    {
        std::apply(f, values);
    }
    scope_guard_2(const scope_guard_2 &) = delete;
};

template <typename F, typename... Args> // 推导指引非常重要
scope_guard_2(F &&, Args &&...) -> scope_guard_2<std::decay_t<F>, std::decay_t<Args>...>;

/// @brief 直接使用模版参数F，可以匹配任意类型，代价是会触发两次copy操作
/// @tparam F
/// @tparam ...Args
template <typename F, typename... Args>
    requires(std::invocable<F, Args...>)
class scope_guard_3
{
  public:
    scope_guard_3(F func, Args... _args) : f{func}, args{_args...}
    {
    }
    ~scope_guard_3()
    {
        dbg("~scope_guard_3");
        std::apply(f, args);
    }
    scope_guard_3(const scope_guard_3 &) = delete;

  private:
    F f;
    std::tuple<Args...> args;
};

template <typename F, typename... Args>
    requires(std::invocable<F, Args...>)
class scope_guard_4
{
};

// 默认情况下选择模板类 A 作为 Test 的实现
template <typename F, typename... Args> struct GuardImpl
{
    using type = scope_guard_3<F, Args...>;
};

// template <typename F, typename... Args> using scope_guard = scope_guard_3<F, Args...>;
template <typename F, typename... Args> using scope_guard = typename GuardImpl<F, Args...>::type;

int main()
{
    {
        // scope_guard的作用之一，是让各种C风格指针接口作为局部变量时也能得到RAII支持
        // 这也是本题的基础要求
        FILE *fp = nullptr;
        try
        {
            fp = fopen("test.txt", "a");
            auto lamda = [&] {
                fclose(fp);
                fp = nullptr;
                std::cout << "guard" << std::endl;
            };
            auto guard = scope_guard<decltype(lamda)>(lamda);

            throw std::runtime_error{"Test"};
        }
        catch (std::exception &e)
        {
            puts(e.what());
        }
        assert(fp == nullptr);
    }
    puts("----------");
    {
        // 附加要求1，支持函数对象调用
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
        } t;
        scope_guard<decltype(t)> guard(t);
    }
}

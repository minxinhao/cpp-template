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
        requires std::invocable<Func, Args...>
    scope_guard_1(Func &&func, Args &&...args)
        : f{[func = std::forward<Func>(func), ... args = std::forward<Args>(args)]() mutable {
              std::invoke(std::forward<std::decay_t<Func>>(func), Args(std::forward<Args>(args))...);
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
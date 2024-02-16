#include "answer.h"

struct X
{
    X()
    {
        puts("X()");
    }
    X(const X &)
    {
        puts("X(const X&)");
    }
    X(X &&) noexcept
    {
        puts("X(X&&)");
    }
    ~X()
    {
        puts("~X()");
    }
};

template <typename F, typename... Args> using scope_guard = scope_guard_2<F, Args...>;


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
            // auto guard = scope_guard<decltype(lamda)>(lamda);
            auto guard = scope_guard_1(lamda);

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
        // auto guard = scope_guard(t);
        // scope_guard<decltype(t)> guard(t);
        scope_guard_1 guard(t);
        // Test &tt = t;
        // auto guard_2 = scope_guard(tt);
    }
    puts("----------");
    {
        // 附加要求1，支持函数对象调用
        struct Test
        {
            void operator()(X *x)
            {
                delete x;
            }
        } t;
        auto x = new X{};
        // auto guard = scope_guard<decltype(t), decltype(x)>(t, x);
        auto guard = scope_guard_1(t, x);
    }
    puts("----------");
    {
        // 附加要求2，支持成员函数和std::ref
        auto x = new X{};
        {
            struct Test
            {
                void f(X *&px)
                {
                    delete px;
                    px = nullptr;
                }
            } t;
            // auto guard = scope_guard<decltype(&Test::f), decltype(&t), decltype(std::ref(x))>{&Test::f, &t, std::ref(x)};
            auto guard = scope_guard_1{&Test::f, &t, std::ref(x)};
        }
        assert(x == nullptr);
    }
}
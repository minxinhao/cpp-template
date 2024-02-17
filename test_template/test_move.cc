#include "dbg.h"
#include <cstdio>

struct X
{
    X(int a)
    {
        dbg("construct");
    }

    // X(const X&) = delete;

    // X(X&&) = delete;

    X(const X &)
    {
        dbg("copy");
    }

    X(X &&)
    {
        dbg("move");
    }

    ~X()
    {
        dbg("de-construct");
    }
};

int main()
{
    X x1(0);
    {
        // 会使用0构造临时对象，然后进行拷贝。
        // 需要拷贝构造函数，但是由于返回值优化而不输出copy。
        X x2 = 0;
    }
    {
        X x3 = x1;
    }
    {
        X x4(x1);
    }
    {
        // 临时对象直接用于构造，而不会copy
        // 因此也不会存在临时对象的销毁。
        X x5{X{1}};
    }
    {
        X x6 = X{1};
    }
}
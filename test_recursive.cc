#include "dbg.h"

template <typename T, int stack_size = 0>
T func(T &&t)
    requires(stack_size >= 0)
{
    if (stack_size == 0)
        return t;
    return t * func<T, stack_size - 1>(t - 1);
}

int main()
{
    func(1);
    return 0;
}
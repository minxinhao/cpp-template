#include "dbg.h"

template <typename... Args> void print(Args... args)
{
    (dbg(args), ...);
}

int main()
{
    print("a", "b", "c");
    print();
}
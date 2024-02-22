#include "dbg.h"
template <typename... Args> 
auto mean(Args... args)
{
    auto res = (args + ...);
    return res / sizeof...(args);
}

int main(){
    dbg(mean(1,2,3,4,5));
    dbg(mean(1.0,2.0,3.33,4,5));
}
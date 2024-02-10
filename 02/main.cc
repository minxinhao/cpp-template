#include "dbg.h"
#include <stddef.h>
// #include <format> // format is not supported by current compiler

void operator""_get_string(const char *str, size_t len)
{
    dbg(str,len);
    // std::format
}

constexpr auto operator""_f(const char* fmt, size_t) {
    return[=]<typename... T>(T&&... Args) { return std::vformat(fmt, std::make_format_args(std::forward<T>(Args)...)); };
}

int main()
{
    "mxh"_get_string;
}
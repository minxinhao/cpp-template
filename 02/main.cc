#include "dbg.h"
#include <stddef.h>
#include <format>

void operator""_get_string(const char *str, size_t len)
{
    dbg(str,len);
}

int main()
{
    "mxh"_get_string;
}
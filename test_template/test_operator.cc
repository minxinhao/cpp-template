#include "dbg.h"
struct MyStruct
{
    int value;

    // bool operator<(const MyStruct &other) const
    // {
    //     return value < other.value;
    // }
};

bool operator<(const MyStruct &obj1, const MyStruct &obj2)
{
    return obj1.value < obj2.value;
}

int main()
{
    MyStruct obj1{10};
    MyStruct obj2{20};
    dbg(obj1.value);
    dbg(obj2.value);
    dbg(obj1 < obj2);
}
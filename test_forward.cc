#include "dbg.h"

template <typename T> void func2(T &&t);

template <typename T> void func(T &&t)
{
    if (!std::is_reference_v<T>)
        dbg("PlainType");
    if (std::is_lvalue_reference_v<T>)
        dbg("LValueReference");
    if (std::is_rvalue_reference_v<T>)
        dbg("RValueReference");
    dbg(t);
    dbg("func2 with forward");
    func2(std::forward<T>(t));
    dbg("func2 with direct pass t");
    func2(t);
}

// 暂时没有解决func自己递归调用的问题，只能额外写一个func2
template <typename T> void func2(T &&t)
{
    if (!std::is_reference_v<T>)
        dbg("PlainType");
    if (std::is_lvalue_reference_v<T>)
        dbg("LValueReference");
    if (std::is_rvalue_reference_v<T>)
        dbg("RValueReference");
    dbg(t);
}

int main()
{
    int source_type = 0;
    int &l_reference = source_type;
    int &&r_reference = std::move(source_type);
        
    dbg(source_type);
    func(source_type);

    dbg(l_reference);
    func(l_reference);

    dbg(r_reference);
    func(r_reference);

    dbg((int &&)(source_type));
    func((int &&)(source_type));

    dbg(std::move(source_type));
    func(std::move(source_type));

    dbg(std::forward<int>(r_reference));
    func(std::forward<int>(r_reference));

    dbg(std::forward<int>(l_reference));
    func(std::forward<int>(l_reference));
}
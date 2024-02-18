#include "dbg.h"
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers = {1, 2, 2, 3, 3, 3, 4, 5, 5};

    // 对向量进行排序
    std::sort(numbers.begin(), numbers.end());

    // 使用 std::unique 去重，返回指向不重复范围末尾的迭代器
    auto unique_end = std::unique(numbers.begin(), numbers.end());
    std::for_each(numbers.begin(), numbers.end(), [](int x) { dbg(x); });
    // 使用 std::erase 删除重复元素后的部分
    numbers.erase(unique_end, numbers.end());

    // 输出结果
    for (const auto &num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
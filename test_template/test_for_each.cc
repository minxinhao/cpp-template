#include "dbg.h"
#include <algorithm>
#include <iostream>
#include <vector>

union TableEntry {
    struct
    {
        uint64_t lock : 1; // In SLT[0]代表：对该位置上的retrain是否产生了多个new submodel，
                           // 还是仅有一个new submodel原地替换。
        uint64_t leaf_region : 7;
        uint64_t synonym_leaf : 8; // In SLT[0] represents the model version
        uint64_t leaf_num : 48;    // In SLT[0] represents the number of SLTs
    };
    uint64_t val;

    void lock_te()
    {
        std::atomic_uint64_t *old_val = reinterpret_cast<std::atomic_uint64_t *>(this);
        TableEntry old_te;
        TableEntry new_te;

        auto init = [&]() {
            old_te.val = old_val->load();
            new_te.val = old_te.val;
            new_te.lock = 1;
        };
        init();
        while (true)
        {
            if (old_te.lock)
                continue;
            if (old_val->compare_exchange_strong(old_te.val, new_te.val))
                return;
            init();
        }
    }

    void print()
    {
        dbg(val);
    }
};

int main()
{
    std::vector<TableEntry> numbers(10);

    std::for_each(numbers.begin(), numbers.end(), [](TableEntry &t) { t.print(); });
    std::for_each(numbers.begin(), numbers.end(), [](TableEntry &t) { t.lock_te(); });
    std::for_each(numbers.begin(), numbers.end(), [](TableEntry &t) { t.print(); });

    return 0;
}
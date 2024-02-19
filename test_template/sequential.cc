#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "dbg.h"
#include "docktest.h"
#include <algorithm>
#include <vector>

// WARNING: this has not been compiled yet
// probably some changes still needed...

template <typename T> std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
{
    out << "vector[size=" << v.size() << "]( ";
    std::copy(begin(v), end(v), std::ostream_iterator<T>(out, ", "));
    out << " )";
    return out;
}

TEST_CASE("sequential_containers, DISABLED_we_can_initialize_a_vector")
{
    {
        // TODO: initialize the vector to contain 1, 2, 3, 4
        std::vector<int> v{1, 2, 3, 4};

        CHECK_EQ(4, v.size());
        CHECK_EQ(1, v.at(0));
        CHECK_EQ(2, v.at(1));
        CHECK_EQ(3, v.at(2));
        CHECK_EQ(4, v.at(3));
    }
    {
        // TODO: initialize the vector to contain tuples (1, "one"), (3, "three")
        std::vector<std::tuple<int, std::string>> v{{1, "one"}, {3, "three"}};

        CHECK_EQ(2, v.size());
        CHECK_EQ(1, std::get<0>(v.at(0)));
        CHECK_EQ("one", std::get<1>(v.at(0)));
        CHECK_EQ(3, std::get<0>(v.at(1)));
        CHECK_EQ("three", std::get<1>(v.at(1)));
    }
}

TEST_CASE("sequential_containers, DISABLED_erase_two_center) ")
{
    // TODO
    // define this function to erase the middle element(s)
    auto erase_middle = [](std::vector<int> &v) {
        size_t num = v.size();
        if (num % 2 == 0)
        {
            size_t middle = num / 2;
            v.erase(v.begin() + middle - 1);
            v.erase(v.begin() + middle - 1);
            v.resize(num - 2);
        }
        else
        {
            size_t middle = num / 2;
            v.erase(v.begin() + middle);
            v.resize(num - 1);
        }
    };

    {
        std::vector<int> values({10, 11, 12, 13, 14, 15});
        erase_middle(values);
        dbg(values);
        CHECK_EQ(std::vector<int>({10, 11, 14, 15}), values);
    }
    {
        std::vector<int> values({10, 11, 12, 13, 14});
        erase_middle(values);
        dbg(values);
        CHECK_EQ(std::vector<int>({10, 11, 13, 14}), values);
    }
}

TEST_CASE("sequential_containers, DISABLED_make_it_unique) ")
{
    // TODO: make no value occur twice
    // hint make_unique and erase are your friends
    auto erase_duplicates = [](std::vector<int> &v) {
        std::sort(v.begin(), v.end());
        dbg(v);
        auto newEnd = std::unique(v.begin(), v.end());
        dbg(v);
        v.erase(newEnd, v.end());
        dbg(v);
    };

    {
        std::vector<int> values({15, 10, 11, 11, 12, 13, 14, 15});
        erase_duplicates(values);
        for (const auto v : {10, 11, 12, 13, 14, 15})
        {
            CHECK_EQ(1u, std::count(begin(values), end(values), v));
        }
    }
}
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
#include <string>

TEST_CASE("range_based_for, DISABLED_rewrite_to_cpp11")
{
    std::vector<int> ints{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result = 0;
    // TODO: convert this C++03 beast into modern c++
    // GOAL: more readable code
    // HINT: range-based for
    // HINT2: later you should use an std::algorithm for this
    for (auto val : ints)
    {
        result += val;
    };
    CHECK_EQ(55, result);
}

template <class Container, class result_type = long> result_type sum(const Container &c)
{
    result_type result = 0;
    for (auto &&data : c)
    {
        result += data;
    }
    return result;
}

TEST_CASE("range_based_for, DISABLED_use_on_generic_containers_also_arrays")
{
    std::vector<int> ints{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    CHECK_EQ(55, sum(ints));
    // TODO:
    // enable this piece of code
    // the `sum` function template won't compile.
    // Adapt the `sum` function template using a range based for loop
    // GOAL:
    // see?  range based for loops allow more generic code!
    long longs[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    CHECK_EQ(55, sum(longs));
}

class Range
{
  public:
    Range(int first, int after_last) : first{first}, after_last{after_last}
    {
    }

    int first;
    int after_last;

    struct Iterator
    {
        int value;
        Iterator &operator++()
        {
            ++value;
            return *this;
        }
        bool operator!=(const Iterator &other) const
        {
            return value != other.value;
        }
        int operator*() const
        {
            return value;
        }
    };

    Iterator begin()
    {
        return Iterator{first};
    };

    Iterator end()
    {
        return Iterator{after_last};
    };
};

TEST_CASE("range_based_for, DISABLED_we_can_iterate_over_a_collection")
{
    int result = 0;
    // TODO: extend the Range class so that it acts as a
    // real 'range' and can be used in a range based for loop.
    //
    // GOAL: understand the working of range-based for loop, and
    // adapt existing classes to it
    //
    // HINT: This is a harder problem: you need to provide
    // a free begin(const Range&) and end(const Range&) function
    // that returns an iterator-like object.
    //
    for (const auto &element : Range{1, 11})
    {
        result += element;
    }
    CHECK_EQ(55, result);
}

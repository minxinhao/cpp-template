#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
#include <unordered_map>
#include <vector>

const auto samples = [](auto f) {
    std::vector<int> values(1000);
    for (int x = 0; x != values.size(); ++x)
    {
        values[x] = static_cast<int>(f(x));
    }
    return values;
};

TEST_CASE("adjacent_find, DISABLED_where_is_the_first_zero_crossing")
{
    const auto values = samples([](auto x) { return x * x * x - 8 * x * x - 13 * x - 4; });

    // TODO: calculate where the function values crosses zero
    // GOAL: learn to use adjacent find (and forget manually chasing pointers)
    // const auto zerocrossing = std::begin(values);
    const auto zerocrossing =
        std::adjacent_find(values.begin(), values.end(), [](auto x, auto y) { return x * y <= 0; });

    CHECK((*zerocrossing) * (*std::next(zerocrossing)) <= 0);
}

const auto make_f = [](auto a, auto b, auto c) {
    return [=](auto x) {
        // https://www.desmos.com/calculator/trpwba2fej
        auto t = (x / 10.0 / b - 10.0 * a);
        return t * t * t - 8 * t * t - 13 * t + c;
    };
};

TEST_CASE("adjacent_find, DISABLED_where_is_the_first_top")
{
    const auto values = samples(make_f(1.1, 10, 6));

    // TODO: calculate where the function values remain equal
    // GOAL: learn to use separate iteration from predicate
    // HINT: 'equal' may means 'close enough to one another', i.e.
    // you may cast to integer.
    // HINT2: the result will be around 10 somewhere.
    // const auto top = std::begin(values);
    const auto top = std::adjacent_find(values.begin(), values.end(), [](auto x, auto y) {
        return static_cast<int64_t>(x) == static_cast<int64_t>(y);
    });

    CHECK_EQ(*top, *std::next(top));
}

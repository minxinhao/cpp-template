#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
#include <algorithm>
#include <array>
#include <utility>

// TODO: increase the usage depth
// until you get a stack overflow
constexpr size_t recursion_depth = 100;

namespace dont_touch_this
{
struct Tiny
{
};

struct Moderate
{
    int value1;
    double value2;
};

struct Big
{
    std::array<int, 100000> data;
};

struct Gigantic
{
    std::array<int, 100000000> data;
};
} // namespace dont_touch_this

namespace
{

template <typename Arg> void use(const Arg& a, size_t depth = recursion_depth)
{
    if (depth)
        use(a, depth - 1);
}
} // namespace

using namespace dont_touch_this;

TEST_CASE("storage_types, DISABLED_evenBigObjectsCanBePassedAroundSomehow")
{
    // TODO: update the `use` function signature
    // in order to make the test pass without
    // stack overflows
    use(Tiny{});
    use(Moderate{});
    use(Big{});
}

TEST_CASE("storage_types, DISABLED_giganticObjectsCantBeOnTheStack")
{
    // TODO: update the allocation
    // in order to make the test pass without
    // stack overflows
    Gigantic* g = new Gigantic();
    use(g);
}

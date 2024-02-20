#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "dbg.h"
#include "docktest.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

struct FormInput
{
    std::string_view value;
};
struct Index
{
    int value;
};
struct Ratio
{
    double value;
};

struct Voltage
{
    double value;
};

std::string to_string(Voltage v)
{
    std::ostringstream ss;
    ss.precision(1); // fixed for this case
    ss << std::fixed << v.value << "V";
    return ss.str();
}

struct VoltageRange
{
    Voltage low;
    Voltage high;
};

Index fromForm(FormInput input)
{
    return {atoi(input.value.data())};
}

Ratio fromIndex(Index i)
{
    return {static_cast<double>(i.value) / 100.0};
}

const VoltageRange range{{1.0}, {10.0}};

Voltage toVoltage(Ratio r)
{
    const auto scale = (range.high.value - range.low.value);
    return {range.low.value + r.value * scale};
}

// The Works: this is called from a `main(argc, argv)` somewhere,
// with `args` filled up with the values in argv
auto toVoltageString(const std::vector<std::string_view> &args)
{
    if (args.size() == 0)
        return std::string("?");
    const auto input = FormInput{args.at(0)};
    if (input.value.length() == 0 || !std::isdigit(input.value[0]))
        return std::string("?");
    const auto index = fromForm(input);

    if (index.value >= 1000 || index.value < 0)
        return std::string("?");
    const auto ratio = fromIndex(index);
    const auto voltage = toVoltage(ratio);
    return to_string(voltage);
}

// Leave this as is: this tests the basic functionality:
// take an argument, convert it to a voltage.
TEST_CASE("optional, we_can_convert_an_argument_to_a_voltage")
{
    CHECK_EQ(toVoltageString({"0"}), "1.0V");
    CHECK_EQ(toVoltageString({"90"}), "9.1V");
    CHECK_EQ(toVoltageString({"100"}), "10.0V");
}

// TODO:
//   adapt `toVoltageString` so that it can work with
//   no arguments at all.  Use `std::optional` on the
//   way to express absence of an argument.
//
//   Do this for the following three tests
//
// GOAL:
//   learn to create an `optional`, and handle
//   invalid ones.
TEST_CASE("optional, DISABLED_we_can_deal_with_lack_of_arguments")
{
    CHECK_EQ(toVoltageString({}), "?");
}

// TODO: same as previous test
TEST_CASE("optional, DISABLED_we_can_deal_with_invalid_numbers")
{
    CHECK_EQ(toVoltageString({"NotANumber"}), "?");
}

// TODO: same as previous test
TEST_CASE("optional, DISABLED_we_can_deal_with_overflow")
{
    CHECK_EQ(toVoltageString({"10000"}), "?");
    CHECK_EQ(toVoltageString({"-10000"}), "?");
}

// TODO:
#define LOOK_MA_IM_DOING_FUNCTORS
// and make the code compile and the tests succeed
//
// Note: this is a little more advanced, requires some template programming
//
#ifdef LOOK_MA_IM_DOING_FUNCTORS
namespace functor
{
// TODO: create a `transform` implementation that
// will convert optional<T> to optional<R>
template <typename T, typename FTR>
auto transform(std::optional<T> what, FTR &&function_T_to_R) -> std::optional<std::invoke_result_t<FTR, T>>
{
    if (!what.has_value())
        return std::nullopt;
    // return what; // you'll want an optional<R> here... declval, decltype anyone?
    return std::invoke(function_T_to_R, std::move(what.value()));
};
} // namespace functor

using namespace functor;
TEST_CASE("optional, DISABLED_make_it_a_functor")
{
    CHECK_EQ(std::optional<Index>{}.has_value(), transform(std::optional<FormInput>{}, fromForm).has_value());

    auto itos = [](int i) { return std::to_string(i); };
    CHECK_EQ(std::optional<std::string>{"1"}.value(), transform(std::optional<int>{1}, itos).value());
    CHECK_EQ(std::optional<std::string>{}.has_value(), transform(std::optional<int>{}, itos).has_value());
}

#endif
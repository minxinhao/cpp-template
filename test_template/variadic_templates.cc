#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "dbg.h"
#include "docktest.h"
#include <string>
#include <vector>

// TODO: alter a function template to return the number of arguments passed.
// GOAL: be able to specify a variadic function template and use the sizeof... operator
// GRADE: ENTRY
#define i_can_specify_a_variadic_function_template
#ifdef i_can_specify_a_variadic_function_template
// template <typename T1 = int, typename T2 = int, typename T3 = int> size_t count_args(T1 = T1{}, T2 = T2{}, T3 = T3{})
// {
//     return 0;
// }
template <typename... Args> size_t count_args(Args... args)
{
    return sizeof...(Args);
}

TEST_CASE("variadic, we_can_count_arguments")
{

    CHECK_EQ(2u, count_args(1, 2));
    CHECK_EQ(3u, count_args("one", 2.0, 3));
}
#endif

// TODO: alter the class template to know its number of arguments
// GOAL: be able to specify a variadic class template and use the sizeof... operator
// GRADE: ENTRY
#define i_can_specify_a_variadic_class_template
#ifdef i_can_specify_a_variadic_class_template

// template <typename T1 = int, typename T2 = int, typename T3 = int> struct CountArgs
// {
//     static constexpr size_t value = 0;
// };

template <typename... Args> struct CountArgs
{
    static constexpr size_t value = sizeof...(Args);
};

TEST_CASE("variadic, we_can_count_arguments2")
{
    CHECK_EQ(2u, (CountArgs<int, bool>::value));
    CHECK_EQ(3u, (CountArgs<int, char, long>::value));
}
#endif

namespace
{

// auto add5(const auto... t)
// {
//     auto add = [](auto val) { return val + 5; };
//     auto make_res = [](auto val...) { return std::make_tuple(add(val)...); };
//     return std::apply(make_res, t);
// }

template <typename T> auto add(const T &val)
{
    return val + 5;
}

template <typename... Args> auto add5(const std::tuple<Args...> args)
{
    // auto add = [](auto val) { return val + 5; };
    auto make_res = [](const auto... val) { return std::make_tuple(add(val)...); };
    return std::apply(make_res, args);
}

} // namespace
TEST_CASE("tuples, DISABLED_i_can_transform_all_elements_of_a_tuple")
{
    // TODO: make `add5` process each element of the `input` tuple
    // to generate a new tuple where each element is 5 bigger
    // GOAL: learn to use pack expansion in function arguments
    // LEVEL: BASIC
    // HINT: return types can be `auto`
    // HINT: make_tuple deduces its template arguments
    const auto input = std::make_tuple(5, 5.0, 'A');
    const auto &result = add5(input);
    CHECK_EQ(10, std::get<0>(result));
    CHECK_EQ(10.0, std::get<1>(result));
    CHECK_EQ('F', std::get<2>(result));
}

namespace
{

template <typename... Ts> std::string serialize(const Ts &...ts)
{
    return "";
}

template <> std::string serialize(const int &ts)
{
    return "int@" + std::to_string(ts);
}

template <> std::string serialize(const std::string &ts)
{
    return "string@'" + ts + "'";
}

template <typename T, typename... Ts> std::string serialize(const T &t, const Ts... rest)
{
    return serialize(t) + "," + serialize(rest...);
}

} // namespace
TEST_CASE("serialization, DISABLED_serialize_different_types")
{
    // TODO: fill in serialize so that the test passes
    // GOAL: get familiar with template parameter packs
    // GOAL: learn how to expand a (single) parameter pack
    // GRADE: INTERMEDIATE
    CHECK_EQ("", serialize());
    CHECK_EQ("int@1", serialize(1));
    CHECK_EQ("string@'abc'", serialize(std::string("abc")));
    CHECK_EQ("int@1, string@'abc'", serialize(1, std::string("abc")));
}

// TODO: implement flatten to allow polymorphic concatenation
// GOAL: learn to separate iteration from dispatching
// HINT: the base case is a single vector
// GRADE: INTERMEDIATE

template <typename T> std::vector<T> flatten(std::vector<T> t1)
{
    dbg("4");
    return t1;
}

template <typename T> std::vector<T> flatten(std::vector<T> t1, T t2)
{
    dbg("3");
    t1.push_back(t2);
    return t1;
}

template <typename T> std::vector<T> flatten(std::vector<T> t1, std::vector<T> t2)
{
    dbg("2");
    t1.insert(t1.end(), t2.begin(), t2.end());
    return t1;
}

template <typename T, typename T2, typename... Ts> std::vector<T> flatten(std::vector<T> t, T2 t2, Ts... ts)
{
    dbg("1");
    return flatten(flatten(t, t2), ts...);
}
TEST_CASE("variadic_monad, DISABLED_flatten_operation")
{
    // flatten(std::vector<int>{},1);
    flatten(std::vector<int>{}, 1, 1);
    // CHECK_EQ((std::vector<int>{1, 2, 3, 4, 5}), (flatten(std::vector<int>({1}), 2, std::vector<int>{3, 4, 5})));
}

// TODO: adapt `contained_by` to return a callable
// representing a predicate for presence in a compile-time list
// HINT: contained_by()( anything ) will return false.
// GRADE: INTERMEDIATE
template <typename... Ts> auto contained_by(Ts &&...ts)
{
    return [](auto x) { return false; };
}

TEST_CASE("variadic_templates, DISABLED_create_a_compile_time_list_lookup")
{
    auto in_list = contained_by(1, 2, 3, 4);
    CHECK(in_list(1));
    CHECK_FALSE(in_list(0));
}

template <typename F, typename A, typename T, typename... Ts> auto accumulate(F f, A a, T t, Ts... ts)
{
    return a;
}

TEST_CASE("variable_templates, DISABLED_we_can_accumulate")
{
    // TODO: create the `accumulate` function template so that
    // it behaves like a compile time accumulation
    // GOAL: create an ingredient for further good
    // LEVEL: INTERMEDIATE
    CHECK_EQ(10, accumulate(std::plus<>(), 0, 1, 8, 1));
    CHECK_EQ(10, accumulate(std::plus<>(), 0, 1, 2, 3, 4));
}

template <typename F, typename T> auto transform(F f, T t)
{
    return t;
};

TEST_CASE("variadic_tuple_iteration, DISABLED_we_can_transform_an_indexed_tuple")
{
    // TODO: create a `transform` function to convert each
    // element of the provided tuple to a corresponding element
    // of a new tuple
    // GOAL: learn to construct a 'helper' argument.  This shows that
    // tuples are Functors, too.
    // HINT: this tuple has elements of the same type.
    // simply iterating using the Type doesn't work anymore.
    // So we need a helper structure/accumulator/loop variable to keep track
    // of the element index we're looking at.
    //
    const auto input = std::make_tuple(1, 2, 3.5);
    const auto f = [](auto i) { return i + 1; };
    const auto result = transform(f, input);
    CHECK_EQ(2, std::get<0>(result));
    CHECK_EQ(3, std::get<1>(result));
    // EXPECT_NEAR(4.5, std::get<2>(result), .0001);
    REQUIRE_EQ(4.5, doctest::Approx(std::get<2>(result)));
}

using Amount = int;
struct Account
{
    Amount balance;
};
auto consult(const Account &a)
{
    return a.balance;
}
auto transaction(Account &from, Account &to, Amount amount)
{
    if (from.balance <= amount)
        return false;
    from.balance -= amount;
    to.balance += amount;
    return true;
}

// TODO:
// uncomment next line
// #define I_CAN_WRAP_FUNCTIONS
//
// And now...
//
// create the `writer` meta-function so that it
// returns a function that
//    * accepts an existing M _and_ all the arguments for `f`
//    * appends `m` to an existing M
//    * returns the tuple { m, f(args) }
//
// GOAL:
//   Learn to work with functions as first class citizens
//   allows you to write more orthogonal code: the code
//   concerned with the logging does not need to have anything to
//   do with the code performing the action.
//
// HINT:
//   use generic lambdas
//   mind reference arguments!  They need to be perfect-forwarded!
//
#ifdef I_CAN_WRAP_FUNCTIONS
template <typename M, typename F> auto writer(M m, F f)
{
}
#endif

TEST_CASE("variadic_templates, DISABLED_can_be_used_to_wrap_existing_functions")
{
    Account mine{1000};
    Account yours{50};

    CHECK(transaction(mine, yours, 50));
    CHECK_EQ(950, mine.balance);
    CHECK_EQ(100, yours.balance);

#ifdef I_CAN_WRAP_FUNCTIONS
    using namespace std::string_literals;
    auto v_consult = writer("consult\n"s, consult);
    auto v_transaction = writer("transaction\n"s, transaction);

    std::string logs0;
    {
        auto [logs1, balance] = v_consult(logs0, mine);
        CHECK_EQ("consult\n", logs1);
        CHECK_EQ(950, balance);
        CHECK_EQ(100, yours.balance);
        auto [logs2, u] = v_transaction(logs1, yours, mine, 50);
        CHECK_EQ("consult\ntransaction\n", logs2);
        CHECK_EQ(true, u);
        CHECK_EQ(1000, mine.balance);
        CHECK_EQ(50, yours.balance);
    }
#endif
}

auto tabulate = [](auto... functions) { return [](auto... arguments) { return std::string{"not implemented"}; }; };

TEST_CASE("composition, DISABLED_print_a_matrix")
{

    // this exercise will take some more time...
    //
    // TODO: fill in the `tabulate` function so that it prints a table
    // of the functions applied to the arguments
    // GOAL: learn to deal with multiple packs and expansions
    // GRADE: HARD
    const auto table =
        tabulate([](auto i) { return i; }, [](auto i) { return i * i; }, [](auto i) { return i * i * i - 1; })(1, 2, 3);
    CHECK_EQ(R"(1, 2, 3
1, 4, 9
0, 7, 26)",
             table);

    CHECK_EQ(R"(1, 4, 9, 100
1, 8, 27, 1000)",
             tabulate([](auto i) { return i * i; }, [](auto i) { return i * i * i; })(1, 2, 3, 10));
}
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "docktest.h"
#include <string>
#include <type_traits>

enum class Type
{
    String,
    Number,
    Array,
    Dict
};
// TODO
#define I_KNOW_GENERICS
//
// and make the tests compile and succeed

#ifdef I_KNOW_GENERICS

template <typename T>
    requires std::is_arithmetic_v<T>
Type getTypeFor(T &&t)
{
    return Type::Number;
}

template <typename T>
    requires std::is_same_v<std::decay_t<T>, std::string> || std::is_convertible_v<T, std::string>
Type getTypeFor(T &&t)
{
    return Type::String;
}

template <typename T>
    requires(!std::is_convertible_v<T, std::string> && std::is_array_v<std::remove_cvref_t<T>>)
Type getTypeFor(T &&t)
{
    return Type::Array;
}

template <typename T> Type getTypeFor(T &&t)
{
    return Type::Dict;
}

TEST_CASE("generic, algorithmCanUseManyInputTypes")
{
    auto s = "abc";

    CHECK_EQ(Type::String, getTypeFor(s));
    CHECK_EQ(Type::String, getTypeFor(std::string{}));
    CHECK_EQ(Type::Number, getTypeFor(1.0));
    CHECK_EQ(Type::Number, getTypeFor(sizeof("")));
}
#endif

// TODO
#define I_KNOW_GENERICS_AND_PARTIAL_SPECIALIZATION
//
// and make the tests compile and succeed

#ifdef I_KNOW_GENERICS_AND_PARTIAL_SPECIALIZATION
TEST_CASE("generic, algorithmEvenKnowsArrayTypes")
{
    int is[5];
    CHECK_EQ(Type::Array, getTypeFor(is));
}
TEST_CASE("generic, algorithmEvenKnowsArrayTypesUnlessForChars")
{
    CHECK_EQ(Type::String, getTypeFor("abc"));
}
#endif
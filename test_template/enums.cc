#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
enum class A : long long
{
    letter,
    number
};

// TODO: enable following enum definition
#define using_enum_classes
//  the compiler will not allow this.  Use an enum class
//  to make it work (and adapt the client code)
//  GOAL: avoid name clashes in enumerates.
//
#ifdef using_enum_classes
enum class B
{
    newspaper,
    letter
};
#endif

TEST_CASE("enums, DISABLED_enums_are_not_confusing")
{
    A character = A::number;
    switch (character)
    {
    case A::letter:
        break;

        // TODO: make it compile
    case A::number:
        break;
    }
}

TEST_CASE("enums, DISABLED_the_size_is_under_control")
{
    // TODO: adapt A so that this test passes
    CHECK_EQ(8, sizeof(A));
}
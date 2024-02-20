#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Instrument.h"
#include "MyBike.h"
#include "Piano.h"
#include "Thing.h"
#include "Vehicle.h"
#include "docktest.h"

#include <utility>

// Question from the class:
// Uniform Initialization: can you specify a member variable default with braces?
//   --> Yes.  It's called a "brace-or-equal-initializer"
//   cf. https://arne-mertz.de/2015/08/new-c-features-default-initializers-for-member-variables/
//
class Person
{
  public:
    int birthyear = 1900;     // <-- equal-initializer
    std::string name{"John"}; // <-- brace-initializer
    std::string given_name{"Doe"};
};

class Child : public Person
{
  public:
    Child(Person parent, int n, std::string name) : Person{n, std::move(name), std::move(parent.given_name)}
    {
    }
};

TEST_CASE("member_initializers, DISABLED_defaults_can_be_specified_in_class")
{
    Person x;
    CHECK_EQ(1900, x.birthyear);
    CHECK_EQ(std::string{"John"}, x.name);
}

TEST_CASE("member_initializers, DISABLED_defaults_can_be_overriden_with_aggregate_constructor")
{
    Person me{1976, "xtofl", "drarip"};
    CHECK_EQ(1976, me.birthyear);
    CHECK_EQ(std::string{"xtofl"}, me.name);
}

TEST_CASE("member_initializers, DISABLED_defaults_can_be_set_by_child_constructor")
{
    Person me{1976, "xtofl", "drarip"};

    Child c{me, 2002, "Natan"};
    CHECK_EQ(std::string{"drarip"}, c.given_name);
}

// TODO:
// visit Thing.h, and rename Thing::size_in_cm to size_in_m.
// The code still compiles.  That's bad.  Make it so that inheritors
// don't compile by accident.
//
// GOAL: learn to conciously design a class for inheritance
//
// HINT: use the `override` keyword

TEST_CASE("class_design, DISABLED_adding_constructors_should_be_trivial")
{
    // TODO: add a constructor Thing(std::string)
    // make Piano and MyBike inherit this constructor with the least amount of code
    // and replication
    //
    // GOAL: make it trivial to add a base class constructors like Thing::Thing(std::string name)
    //
    // HINT: `using` is the key
    Piano p{"my piano"};
    MyBike b{"my bike"};

    CHECK_EQ("making music", p.purpose());
    CHECK_EQ("my piano", p.name());

    CHECK_EQ("transporting", b.purpose());
    REQUIRE(60.0 == doctest::Approx(b.size_in_cm()));
}

// TODO: alter the needed classes to make it impossible to copy things
// GOAL: learn to use `delete` qualifier
TEST_CASE("class_design, DISABLED_synthesized_functions")
{
    Piano p{""};
    auto q = p; // should not compile.
}
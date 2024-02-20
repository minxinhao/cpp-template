#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
#include <array>
#include <functional>
#include <memory>

class JarPotVessel
{
  public:
    std::function<void()> destructed = [] {};
    ~JarPotVessel()
    {
        destructed();
    }
};

TEST_CASE("unique_ptr, DISABLED_object_is_destructed_when_ptr_out_of_scope")
{
    // TODO: make `thing_wrapper` 'own' the object,
    // to prevent it from leaking
    // GOAL: learn to use unique_ptr to express ownership of
    // objects on the free store.
    auto thing_wrapper = std::make_unique<JarPotVessel>(JarPotVessel());
    bool destructed = false;
    thing_wrapper->destructed = [&] { destructed = true; };

    {
        CHECK_FALSE(destructed);
        auto other_wrapper = std::move(thing_wrapper); // there must be only one!
        CHECK_FALSE(destructed);
    };
    CHECK(destructed);
}

TEST_CASE("unique_ptr, DISABLED_cant_copy_a_unique_ptr")
{
// TODO:
#define i_know_what_is_wrong
// and make the code compile:
// a vector of owners can't be copied, since then there would be
// two owners of each contained object.
#ifdef i_know_what_is_wrong
    std::array<std::unique_ptr<int>, 2> values{
        std::make_unique<int>(1),
        std::make_unique<int>(2),
    };

    CHECK_EQ(1, *values.at(0));
    CHECK_EQ(2, *values.at(1));

    // TODO: tinker with this line to let the test pass
    auto target = std::move(values);

    CHECK_EQ(1, *target.at(0));
    CHECK_EQ(2, *target.at(1));
#endif
}

TEST_CASE("unique_ptr, DISABLED_cant_copy_a_unique_ptr_wrapped_in_initializer_list")
{
// TODO:
#define i_can_create_a_vector_with_unique_ptrs
    // work around the fact that the initializer list uses value semantics
    //
    // HINT: create a bare array, and use a move_iterator
    std::vector<std::unique_ptr<int>> tmp;
#ifdef i_can_create_a_vector_with_unique_ptrs
    tmp.push_back(std::make_unique<int>(1));
    tmp.push_back(std::make_unique<int>(1));
    tmp.push_back(std::make_unique<int>(1));
    tmp.push_back(std::make_unique<int>(1));
#endif
}
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "HeavyObject.h"
#include "dbg.h"
#include "docktest.h"
#include "perftest.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// TODO: add move support to `HeavyObject` class
// no need to touch the code in this test
// NOTE: if the test succeeds without code, increment e.g. Consumer::size until it fails, first.
// GOAL: learn how to add move support to a class
//
TEST_CASE("move, DISABLED_speed_this_up_by_adding_move_support")
{
    auto constructing_objects = duration(
        [&] {
            // construct
            std::array<Heavy, Consumer::size> prototype;
            std::generate(begin(prototype), end(prototype), [] { return Heavy{1000}; });
            // and do stuff with it so that this loop
            // can't be optimized away (by the compiler)
            Consumer::access(prototype);
        },
        1'000);

    auto consuming_objects = duration(
        [&] {
            // construct
            std::array<Heavy, Consumer::size> prototype;
            std::generate(begin(prototype), end(prototype), [] { return Heavy{1000}; });
            // and move to sink
            Consumer cons(std::move(prototype));
        },
        1'000);

    CHECK_LT(consuming_objects, constructing_objects * 1.1);
    // << "consuming: " << consuming_objects << " vs. constructing: " << constructing_objects;
}

class Resource
{
  public:
    Resource(std::string id) : id{std::move(id)}
    {
    }

    Resource(const Resource &other) : id{other.id}
    {
        dbg("copy cons");
        Resource & ref = const_cast<Resource &>(other);
        ref.id = std::string("invalid");
        dbg("copy cons end");
    }

    Resource(Resource &&other) : id{std::move(other.id)}
    {
    }

    Resource &operator=(const Resource &other)
    {
        dbg("copy =");
        id = std::move(other.id);
        Resource & ref = const_cast<Resource &>(other);
        ref.id = std::string("invalid");

        return *this;
    }

    Resource &operator=(Resource &&other)
    {
        dbg("move =");
        if (this != &other)
        {
            id = std::move(other.id);
            other.id = std::string("invalid");
        }

        return *this;
    }

    std::string id;
};

// TODO: alter the `Pool` class so that
// the contained resources have move semantics:
// a borrowed resource is no longer in the pool.
//
// GOAL: implementing functions that transfer ownership
// NOTE: try to make sure the user doesn't _accidentally_
// lose an object (think of the API!)
// HINT: rvalue references to the rescue
TEST_CASE("move, DISABLED_there_should_be_only_one_owner")
{
    class Pool
    {
      public:
        Pool() : resources{{Resource{"one"}, Resource{"two"}}}
        {
        }
        size_t size() const
        {
            return resources.size();
        }

        // TODO: make sure that a borrowed resource
        // is no longer in the pool
        // (it can only be borrowed once!)
        Resource borrow()
        {
            Resource r{resources.front()};
            resources.erase(resources.begin());
            return r;
        }

        // TODO: make sure that the returned
        // resource can be borrowed again
        void return_(Resource r)
        {
            dbg("return");
            resources.push_back(r);
        }

        // don't touch this
        bool contains(const std::string &id) const
        {
            return std::any_of(begin(resources), end(resources),
                               [&](const auto &resource) { return resource.id == id; });
        }

      private:
        std::vector<Resource> resources;
    };

    Pool pool;
    auto r1 = pool.borrow();
    CHECK_EQ("one", r1.id);
    CHECK_EQ(1u, pool.size());
    CHECK_FALSE(pool.contains("one"));
    CHECK(pool.contains("two"));

    pool.return_(r1);
    CHECK_EQ(2u, pool.size());
    CHECK(pool.contains("one"));
    CHECK(pool.contains("two"));
    CHECK_EQ(r1.id, "invalid"); // this requires tinkering with the `Resource` class
}
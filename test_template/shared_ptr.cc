#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
#include <functional>
#include <memory>

namespace
{
class Resource
{
  public:
    void use()
    {
        ++usage_count;
    }

    ~Resource()
    {
        destructed();
    }

    int usage_count = 0;
    std::function<void()> destructed = [] {};
};

class User
{
  public:
    void foo()
    {
        resource.get()->use();
    }
    std::shared_ptr<Resource> resource;
};

} // namespace

TEST_CASE("shared_ptr, DISABLED_resource_is_cleant_up_after_last_user_gone")
{
    // TODO: identify Resource owners, and adapt their containment of Resource
    // so that the Resource can be shared.
    //
    // GOAL: you don't need raw pointers
    auto resource = std::make_shared<Resource>(Resource());
    bool destructed = false;
    resource->destructed = [&] { destructed = true; };

    std::vector<User> users;
    CHECK_FALSE(destructed);

    users.emplace_back(User{resource});
    CHECK_FALSE(destructed);
    users.emplace_back(User{resource});
    CHECK_FALSE(destructed);

    auto users_copy = users;
    CHECK_FALSE(destructed);

    users.clear();
    CHECK_FALSE(destructed);

    users_copy.clear();
    resource = nullptr;
    CHECK(destructed);
}

class Pool
{
  public:
    using Handle = int;
    std::set<Handle> handles;
    Handle next_free_handle = Handle{};
    Handle allocate()
    {
        auto h = next_free_handle++;
        handles.insert(h);
        return h;
    }
    void free(Handle h)
    {
        handles.erase(h);
    }

    bool allocated(Handle h)
    {
        return handles.find(h) != end(handles);
    }
};

TEST_CASE("shared_ptr, DISABLED_not_only_for_objects")
{
    Pool pool;
    try
    {
        // TODO: adapt h so that even in case of
        // an exception, it is freed after usage
        // GOAL: make sure h does not leak
        // hint: shared_ptr has two arguments!
        // auto h = pool.allocate();
        std::shared_ptr<Pool::Handle> h(new Pool::Handle(pool.allocate()), [&pool](Pool::Handle *h) {
            pool.free(*h);
            delete h;
        });

        CHECK_EQ(0, *h.get());
        // CHECK_EQ(0, h);
        throw std::runtime_error("");
    }
    catch (const std::runtime_error &)
    {
        CHECK_FALSE(pool.allocated(0));
    }
}

class Child;

class Parent
{
  public:
    std::vector<std::shared_ptr<Child>> children;
    std::function<void()> call = [] {};
    std::function<void()> destructed = [] {};
    ~Parent()
    {
        destructed();
    }
};

class Child
{
  public:
    Child(std::shared_ptr<Parent> parent) : parent(std::move(parent))
    {
    }
    void call_parent()
    {
        if (auto p = parent.lock())
        {
            p->call();
        }
    }
    std::weak_ptr<Parent> parent;
    std::function<void()> destructed = [] {};
    ~Child()
    {
        destructed();
    }
};

TEST_CASE("shared_ptr, DISABLED_breaking_cycles")
{
    // TODO: change the parent-child containment so that it
    // is impossible to create a resource leak by cyclic reference
    // GOAL: expressing aggregation and composition
    //
    bool parent_destructed = false;
    bool parent_called = false;
    bool child_destructed = false;
    {
        auto parent = std::make_shared<Parent>();
        parent->destructed = [&] { parent_destructed = true; };
        parent->call = [&] { parent_called = true; };

        parent->children.emplace_back(std::make_shared<Child>(parent));
        parent->children.back()->destructed = [&] { child_destructed = true; };

        parent->children.back()->call_parent();
        CHECK(parent_called);
    }
    CHECK(parent_destructed);
    CHECK(child_destructed);
}
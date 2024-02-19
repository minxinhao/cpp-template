#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "docktest.h"
#include <algorithm>
#include <chrono>
#include <future>
#include <thread>

#include "ingredients.hpp"
#include "perftest.h"

struct Bolognese
{
    Ingredient<Diced<Carrot>> carrots;
    Ingredient<Diced<Paprika>> paprika;
    Ingredient<Cooked<Grated<Meat>>> meat;
};

auto make_sauce()
{
    // Bolognese sauce{diced(Carrot{}, 400), diced(Paprika{}, 200), cooked(Grated<Meat>{}, 250)};
    auto dice_carrot = std::async(std::launch::async, []() { return diced(Carrot{}, 400); });

    auto dice_paprika = std::async(std::launch::async, []() { return diced(Paprika{}, 200); });

    auto cook_meat = std::async(std::launch::async, []() { return cooked(Grated<Meat>{}, 250); });
    Bolognese sauce{dice_carrot.get(),dice_paprika.get(),cook_meat.get()};
    
    return Ingredient<Bolognese>{sauce, 1000};
}

struct PastaBolognese
{
    Ingredient<Cooked<Pasta>> pasta;
    Ingredient<Grated<Emmental>> cheese;
    Ingredient<Bolognese> sauce;
};

auto make_pasta()
{
    // auto pasta = PastaBolognese{cooked(Pasta{}, 500), grated(Emmental{}, 500), Ingredient<Bolognese>{make_sauce()}};
    auto pastaFuture = std::async(std::launch::async, []() { return cooked(Pasta{}, 500); });

    auto cheeseFuture = std::async(std::launch::async, []() { return grated(Emmental{}, 500); });

    auto sauceFuture = std::async(std::launch::async, []() { return Ingredient<Bolognese>{make_sauce()}; });

    auto pasta = PastaBolognese{pastaFuture.get(), cheeseFuture.get(), sauceFuture.get()};
    return pasta;
}

TEST_CASE("AsyncTest, DISABLED_we_can_do_things_in_parallel")
{
    // TODO: tweak the make_pasta and make_sauce functions
    // to do stuff in parallel
    //
    // PURPOSE: learn to use async and gather results from async operations
    CHECK_GT(1500_ms, duration([&] { auto pasta = make_pasta(); }, 1));
}
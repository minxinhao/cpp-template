#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "dbg.h"
#include "docktest.h"
#include <algorithm>
#include <random>
#include <vector>

namespace
{
template <class Container> struct Contains
{
    const Container &container;
    Contains(const Container &c) : container(c)
    {
    }

    template <class T> bool operator()(const T &value) const
    {
        return std::find(std::begin(container), std::end(container), value) != std::end(container);
    };
};

template <class Container> Contains<Container> contains(const Container &c)
{
    return Contains<Container>(c);
}

template <class Container> struct ContainsIf
{
    const Container &container;
    ContainsIf(const Container &c) : container(c)
    {
    }
    using value_type = typename Container::value_type;
    template <class F> bool operator()(const F &f) const
    {
        return std::find_if(std::begin(container), std::end(container), f) != std::end(container);
    };
};

template <class Container> ContainsIf<Container> contains_if(const Container &c)
{
    return ContainsIf<Container>(c);
}

TEST_CASE("test_the_test, contains_works")
{
    const std::vector<int> values{1, 2, 3, 4};
    const auto check = contains(values);
    CHECK(check(2));
    CHECK(check(4));
    CHECK_FALSE(check(5));
}

TEST_CASE("test_the_test, contains_if_works")
{
    const std::vector<int> values{1, 2, 3, 4};
    const auto check = contains_if(values);
    CHECK(check([](int v) { return v % 2 == 0; }));
    CHECK(check([](int v) { return v == 3; }));
    CHECK_FALSE(check([](int v) { return v > 10; }));
}
} // namespace

TEST_CASE("sets, DISABLED_remove_duplicates")
{
    std::vector<int> values{1, 2, 2, 3, 4, 5, 6, 6, 8, 8, 9};
    // TODO: remove duplicates from `values`
    // HINT: only 'unique' values should be present
    std::unordered_set<int> set(values.begin(), values.end());
    values.assign(set.begin(), set.end());

    for (const auto value : values)
    {
        CHECK_EQ(1, std::count(std::begin(values), std::end(values), value));
    }
}

TEST_CASE("sets, DISABLED_remove_duplicates_2")
{
    std::vector<int> values{1, 2, 2, 3, 4, 5, 6, 6, 8, 8, 9};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(std::begin(values), end(values), g);
    // TODO: remove duplicates from `values`
    // HINT: read the preconditions for `unique`!
    std::unordered_set<int> set(values.begin(), values.end());
    values.assign(set.begin(), set.end());

    for (const auto value : values)
    {
        CHECK_EQ(1, std::count(std::begin(values), std::end(values), value));
    }
}

struct Person
{
    std::string name;
    std::string surname;
};

bool operator==(const Person &p1, const Person &p2)
{
    return std::tie(p1.name, p1.surname) == std::tie(p2.name, p2.surname);
}

bool operator<(const Person &p1, const Person &p2)
{
    // return std::tie(p1.name, p1.surname) < std::tie(p2.name, p2.surname);
    return p1.surname < p2.surname;
}

std::vector<Person> classmates{{"Ton", "Lathauwers"}, {"Filip", "Dickens"}, {"Stephan", "De Schrijver"}};
std::vector<Person> colleagues{{"Ton", "Sauerplum"}, {"Filip", "Dickens"}, {"Johan", "De Schrijver"}};

TEST_CASE("WithSomeData, DISABLED_find_common_elements")
{
    // TODO: implement `common_surnames` to make the tests succeed
    // GOAL: learn that you can use a Comparison function
    // to treat objects as 'same' or 'less'
    //
    struct PersonHash
    {
        size_t operator()(const Person &p) const
        {

            // return std::hash<std::string>()(p.surname)+std::hash<std::string>()(p.name);
            // 在 std::unordered_set 中，当两个元素的哈希值相同时，会使用等价比较运算符（==）来判断它们是否相等。
            // 只有在哈希值相同且等价比较运算符返回 true 的情况下，才会被视为相同的键。
            // 因此需要保证surname相同的persion，其hash也相同

            // 为了通过最后一个测试，unorded-set就不太好用了
            return std::hash<std::string>()(p.surname);
        }
    };

    auto common_surnames = [](const std::vector<Person> &first,
                              const std::vector<Person> &second) -> std::vector<Person> {
        // std::unordered<Person, PersonHash> set1(first.begin(), first.end());
        // std::unordered<Person, PersonHash> set2(second.begin(), second.end());
        std::set<Person> set1(first.begin(), first.end());
        std::set<Person> set2(second.begin(), second.end());

        std::vector<Person> res;
        std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res));
        return res;
    };
    const auto common = common_surnames(classmates, colleagues);

    CHECK_EQ(2u, common.size());

    const auto common_contains_if = contains_if(common);
    const auto contains_surname = [&](const std::string n) {
        return common_contains_if([&](const Person &p) { return p.surname == n; });
    };
    CHECK(contains_surname("Dickens"));
    CHECK(contains_surname("De Schrijver"));
    CHECK_FALSE(contains_surname("Lathauwers"));
    CHECK_FALSE(contains_surname("Sauerplum"));
}

TEST_CASE("WithSomeData, DISABLED_find_lost_classmates")
{
    // TODO: implement `in_second_but_not_in_first` to make the tests succeed
    // GOAL: get to know some set algorithms
    auto in_second_but_not_in_first = [](const std::vector<Person> &first,
                                         const std::vector<Person> &second) -> std::vector<Person> {
        auto print_data = [](auto &data) {
            std::cout << "-----------\n";
            std::for_each(data.begin(), data.end(),
                          [](const Person &p) { std::cout << p.name << " " << p.surname << "\n"; });
        };
        print_data(first);
        print_data(second);
        // set 内部需要的是一个比较顺序的函数
        auto cmp = [](const Person &p1, const Person &p2) -> bool {
            return std::tie(p1.name, p1.surname) > std::tie(p2.name, p2.surname);
        };
        std::set<Person, decltype(cmp)> set1(first.begin(), first.end());
        std::set<Person, decltype(cmp)> set2(second.begin(), second.end());
        std::vector<Person> res;
        std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(res), cmp);
        print_data(res);
        return res;
    };
    const auto lost = in_second_but_not_in_first(classmates, colleagues);

    CHECK_EQ(2u, lost.size());
    const auto lost_contains_if = contains_if(lost);
    const auto lost_person = [&](const Person &p) {
        return lost_contains_if([&](const Person &p2) { return p == p2; });
    };
    CHECK(lost_person({"Ton", "Lathauwers"}));
    CHECK(lost_person({"Stephan", "De Schrijver"}));
    CHECK_FALSE(lost_person({"Filip", "Dickens"}));
    CHECK_FALSE(lost_person({"Ton", "Sauerplum"}));
    CHECK_FALSE(lost_person({"Johan", "De Schrijver"}));
}
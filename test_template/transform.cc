
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
#include <unordered_map>
#include <vector>

TEST_CASE("apply_transform, DISABLED_basic_arithmetic")
{
    const std::vector<int> xs{{2, 5, 10, 40}};
    std::vector<int> squares;

    // TODO: use algorithms to calculate the square of each element
    {
        // naive solution
        // auto f = [&]() {
        //     squares.resize(xs.size());
        //     for (int i = 0; auto data : xs)
        //         squares[i++] = data * data;
        // };
        // f();
    }
    {
        squares.resize(xs.size());
        std::transform(xs.begin(), xs.end(), squares.begin(), [](int x) { return x * x; });
    }

    CHECK_EQ(xs.size(), squares.size());
    CHECK_EQ(4, squares[0]);
    CHECK_EQ(25, squares[1]);
    CHECK_EQ(100, squares[2]);
    CHECK_EQ(1600, squares[3]);
}

TEST_CASE("apply_transform, DISABLED_string_representation")
{
    const std::vector<int> xs{{2, 5, 10, 40}};

    std::vector<std::string> squares;
    // TODO: use algorithms to transform xs into the
    // string representation of their squares
    // GOAL: use a more complex transformation
    {
        squares.resize(xs.size());
        std::transform(xs.begin(), xs.end(), squares.begin(), [](int x) { return std::to_string(x * x); });
    }

    CHECK_EQ(xs.size(), squares.size());
    CHECK_EQ("4", squares[0]);
    CHECK_EQ("25", squares[1]);
    CHECK_EQ("100", squares[2]);
    CHECK_EQ("1600", squares[3]);
}

TEST_CASE("apply_transform, DISABLED_extract_map_keys")
{
    const std::vector<std::pair<std::string, int>> numbers{{{"two", 2}, {"five", 5}, {"ten", 10}, {"forty", 40}}};

    std::vector<std::string> keys;
    // TODO: extract the keys of the `numbers` map
    // using a `transform`
    {
        keys.resize(numbers.size());
        std::transform(numbers.begin(), numbers.end(), keys.begin(),
                       [](const std::pair<std::string, int> &p) { return p.first; });
    }

    CHECK_EQ(numbers.size(), keys.size());
    CHECK_EQ("two", keys[0]);
    CHECK_EQ("five", keys[1]);
    CHECK_EQ("ten", keys[2]);
    CHECK_EQ("forty", keys[3]);
}

TEST_CASE("apply_transform, DISABLED_join_two_input_ranges")
{
    const std::vector<std::string> keys{{"two", "five", "ten", "forty"}};
    const std::vector<int> values{{2, 5, 10, 40}};

    std::vector<std::string> numbers;

    {
        numbers.resize(values.size());
        std::transform(keys.begin(), keys.end(), values.begin(), numbers.begin(),
                       [](const std::string &s, int data) { return s +": "+ std::to_string(data); });
    }
    // TODO: transform keys and values into
    // this python-key-value syntax
    // GOAL: see that `transform` can accept two ranges
    // and 'zip' them together
    CHECK_EQ(keys.size(), numbers.size());
    CHECK_EQ("two: 2", numbers[0]);
    CHECK_EQ("five: 5", numbers[1]);
    CHECK_EQ("ten: 10", numbers[2]);
    CHECK_EQ("forty: 40", numbers[3]);
}

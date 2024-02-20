#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

TEST_CASE("uniform_initialization, DISABLED_initialize_builtins")
{
    // TODO: initialize the variables to make the expectations pass
    // Use uniform initialization syntax.
    int a{5};
    CHECK_EQ(5, a);
    int *a_pointer{&a}; // yey a leak
    CHECK(&a == a_pointer);
    int an_array[5] = {5, 5, 5, 5, 5};
    CHECK_EQ(5, an_array[4]);
    std::string a_string = "abc";
    CHECK_EQ("abc", a_string);
}

TEST_CASE("uniform_initialization, DISABLED_initialize_a_vector")
{
    // TODO: initialize the variables to make the expectations pass
    std::vector<int> ints = {1, 2, 3, 4, 5};
    CHECK_EQ(5u, ints.size());
    CHECK_EQ(1, ints.at(0));
    CHECK_EQ(2, ints.at(1));
    CHECK_EQ(3, ints.at(2));
    CHECK_EQ(4, ints.at(3));
    CHECK_EQ(5, ints.at(4));
}

TEST_CASE("uniform_initialization, DISABLED_initialize_a_map")
{
    // TODO: initialize the variables to make the expectations pass
    std::map<int, char> ascii = {{65, 'a'}, {66, 'b'}};
    CHECK_EQ('a', ascii.at(65));
    CHECK_EQ('b', ascii.at(66));
}

// TODO: specify the members of this class
// so that they are properly default-initialized
//
struct ProtocolMessage
{
    using ConversationId = int;
    enum class Type
    {
        uninitialized,
        number,
        text
    };
    using Bytes = std::vector<std::uint8_t>;

    ConversationId conversation;
    Type type;
    Bytes bytes;

    ProtocolMessage() : type(Type::uninitialized), conversation(-1), bytes(0)
    {
    }
    ProtocolMessage(const char *str) : type(Type::text), conversation(10), bytes(strlen(str))
    {
        memcpy(bytes.data(), str, sizeof(char) * strlen(str));
    }
    ProtocolMessage(long)
    {
    }
};

TEST_CASE("uniform_initialization, DISABLED_initialize_an_object")
{
    // TODO: specify ProtocolMessage to make the expectations pass
    // GOAL: learn to use member defaults
    CHECK_EQ(ProtocolMessage::Type::uninitialized, ProtocolMessage{}.type);
    CHECK_EQ(-1, ProtocolMessage{}.conversation);
    CHECK_EQ(0, ProtocolMessage{}.bytes.size());

    // TODO: use uniform initializer syntax to properly initialize
    // the message
    const ProtocolMessage message("ab");

    CHECK_EQ(ProtocolMessage::Type::text, message.type);
    CHECK_EQ(10, message.conversation);
    CHECK_EQ(2u, message.bytes.size());
    CHECK_EQ('a', message.bytes.at(0));
    CHECK_EQ('b', message.bytes.at(1));
}

// TODO
//   and make the code compile and the test succeed.
//   by adding an initializer list argument
//
// GOAL:
//   learn to create functions accepting an initializer list
//
// NOTE: a variadic template would be better.
std::string concatenate(std::initializer_list<std::string> list)
{
    std::string res;
    for (auto &str : list)
        res += str;
    return res;
}

template <typename... Args> std::string concatenate(Args... args)
{
    std::string res;
    (res += ... += args);
    return res;
}
TEST_CASE("uniform_initialization, DISABLED_initializer_list_concat")
{
    CHECK_EQ("", concatenate({}));
    CHECK_EQ("abcdefghi", concatenate("abc", "def", "ghi"));
    CHECK_EQ("abcdefghi", concatenate({"abc", "def", "ghi"}));
}
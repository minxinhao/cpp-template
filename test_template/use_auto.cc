#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
#include <map>
#include <string>
#include <vector>

// CODE UNDER TEST:
using Language = std::string;
using Word = std::string;
using Number = int;
using LanguageLib = std::map<Language, std::map<Word, Number>>;

LanguageLib mappings{{"nl-nl", {{"een", 1}, {"twee", 2}}}, {"en-en", {{"one", 1}, {"two", 2}}}};

namespace detail
{
// TODO: reduce type verbosity using deferred function type...
// GOAL: learn that lengthy types are no longer needed in C++ 11+
// template <class Library, class Level1Key, class Level2Key>
// typename Library::value_type::second_type::value_type::second_type find_two_level(const Library &library,
//                                                                                   const Level1Key &key1,
//                                                                                   const Level2Key &key2)
// {
//     return typename Library::value_type::second_type::value_type::second_type();
// }
template <class Library, class Level1Key, class Level2Key>
auto find_two_level(const Library &library, const Level1Key &key1, const Level2Key &key2)
{
    return library.at(key1).at(key2);
}
} // namespace detail

int find_number(const Word &name)
{
    for (auto &lang : mappings)
    {
        auto it = lang.second.find(name);
        if (it != lang.second.end())
            return it->second;
    }
    throw std::range_error("Word not found");
}

int translate(const Language &language, const Word &name)
{
    return detail::find_two_level(mappings, language, name);
}

void set_entry(const Language &language, Word word, int i)
{
    mappings[language][word] = i;
}

TEST_CASE("find_number, DISABLED_we_can_just_auto_translate")
{
    // TODO: enable the test and implement `find_number` to make it succeed
    //
    // GOAL: learn to use the `auto` keyword for local variables
    // and see that complex types are not hard to use
    //
    // HINT: return the first entry containing a language that defines the given word
    // HINT: use the power of range-based for.
    // HINT: or... more advanced... an stl algorithm with some lambda expressions
    CHECK_THROWS_AS(find_number("zork"), std::range_error);
    CHECK_EQ(1, find_number("een"));
    CHECK_EQ(2, find_number("twee"));
    CHECK_EQ(1, find_number("one"));
    CHECK_EQ(2, find_number("two"));
}

TEST_CASE("change_number, DISABLED_we_can_change_entries")
{
    CHECK_NOTHROW(set_entry("en-en", "three", 3));
    CHECK_EQ(3, translate("en-en", "three"));
}

TEST_CASE("change_number, DISABLED_we_can_use_generic_lookup_with_deferred_return_type")
{
    CHECK_EQ(1, detail::find_two_level(mappings, "nl-nl", "een"));
}
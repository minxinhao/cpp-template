#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
#include <iostream>
#include <string>

// WARNING: this has not been compiled yet
// probably some changes still needed...

// TODO:
//  complete these functions to make the tests pass
namespace
{
struct Data
{
    int i;
    std::string s;
    double d;
};
Data read(std::istream &in)
{
    Data d;

    if (!(in >> d.i >> d.s >> d.d))
    {
        throw std::runtime_error("Failed to read data");
    }
    return d;
}
std::ostream &write(std::ostream &out, const Data &data)
{
    out << std::to_string(data.i) << " " << data.s << " " << std::fixed << std::setprecision(1) << data.d;
    // out << data.i << " " << data.s << " " << data.d;
    return out;
}
} // namespace

TEST_CASE("formatted_io, DISABLED_we_can_read_basic_types_from_streams")
{
    std::string s_data("1 abc 200.5");
    std::stringstream ss(s_data);

    // TODO: tweak the `read` function so that it reads in the members
    // of the Data object
    auto data = read(ss);
    CHECK_EQ(1, data.i);
    CHECK_EQ("abc", data.s);
    REQUIRE(data.d == doctest::Approx(200.5));
}

TEST_CASE("formatted_io, DISABLED_we_can_handle_bad_formatting_with_an_exception")
{
    std::string s_data("1 abc not_a_floating_point");
    std::stringstream ss(s_data);

    // TODO: when either member cannot be read, make sure an exception
    // is thrown (we don't want invalid data to exist!)
    CHECK_THROWS_AS(read(ss), std::runtime_error);
}

TEST_CASE("formatted_io, DISABLED_we_can_handle_end_of_stream_with_an_exception")
{
    std::string s_data("1 abc");
    std::stringstream ss(s_data);

    // TODO: when either member cannot be read, make sure an exception
    // is thrown (we don't want invalid data to exist!)
    CHECK_THROWS_AS(read(ss), std::runtime_error);
}

TEST_CASE("formatted_io, DISABLED_we_can_write_basic_types_from_streams")
{
    std::string s_data;
    std::stringstream ss(s_data);

    Data data{1, "xyz", 5.0};
    write(ss, data);
    std::cout << ss.str();
    s_data = ss.str();
    CHECK_EQ("1 xyz 5.0", s_data);
}

TEST_CASE("formatted_io, DISABLED_we_can_print_numbers_in_hex")
{
    std::stringstream ss;

    // ss << 0xabcd;
    ss << std::uppercase << std::hex << std::setw(8) << std::setfill('0') << 0xabcd;

    CHECK_EQ("0000ABCD", ss.str());
}
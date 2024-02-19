#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "dbg.h"
#include "docktest.h"
#include <algorithm>
#include <numeric>
#include <vector>

namespace
{
enum Edge
{
    in,
    out,
    equal
};
struct Stroke
{
    int first;
    int after_last;
};
bool operator==(const Stroke &lhs, const Stroke &rhs)
{
    return lhs.first == rhs.first && lhs.after_last == rhs.after_last;
}
using Strokes = std::vector<Stroke>;
} // namespace

TEST_CASE("adjacent_difference, DISABLED_where_are_the_edges")
{
    // TODO: define edges(...) so that the tests pass
    // GOAL: learn to transform adjacent values
    auto edges = [](const auto &samples) -> std::vector<Edge> {
        int num = strlen(samples);
        if (num == 0)
            return std::vector<Edge>();
        std::vector<int> res(num);
        std::adjacent_difference(samples, samples + num, res.begin());
        std::vector<Edge> edge_res;
        edge_res.resize(num - 1);
        std::transform(res.begin() + 1, res.end(), edge_res.begin(), [](int data) -> Edge {
            constexpr int in_data = 'X' - '.';
            constexpr int out_data = '.' - 'X';
            switch (data)
            {
            case 0:
                return Edge::equal;
            case in_data:
                return Edge::in;
            case out_data:
                return Edge::out;
            default:
                return Edge::in;
            }
        });
        // edge_res.erase(edge_res.begin());
        return edge_res;
    };
    using Edges = std::vector<Edge>;
    CHECK_EQ(Edges{}, edges(""));
    CHECK_EQ((Edges{{equal, in, out}}), edges("..X."));
    {
        dbg((Edges{{equal, in, out}}));
        auto data = edges("..X.");
        dbg(data);
    }
    CHECK_EQ((Edges{{out, equal, equal, in, equal, out}}), edges("X...XX."));
    {
        dbg((Edges{{out, equal, equal, in, equal, out}}));
        auto data = edges("X...XX.");
        dbg(data);
    }
}

TEST_CASE("adjacent_difference, DISABLED_what_is_the_longest_stripe")
{
    // TODO: define edges(...) so that the tests pass
    // GOAL: learn to transform adjacent values

    auto runs = [](const auto &samples) -> std::vector<Stroke> {
        int num = strlen(samples);
        if (num == 0)
            return Strokes{};

        std::vector<int> res(num);
        std::adjacent_difference(samples, samples + num, res.begin());
        std::vector<Stroke> res_stroke;
        Stroke s;
        for (int i = 0; i < num; i++)
        {
            if (res[i] == int('X' - '.'))
            {
                s.first = i;
            }
            if (res[i] == int('.' - 'X'))
            {
                s.after_last = i;
                res_stroke.push_back(s);
            }
        }
        return res_stroke;
    };
    CHECK_EQ(Strokes{}, runs(""));
    CHECK_EQ((Strokes{Stroke{2, 3}}), runs("..X."));
    {
        auto data = runs("..X.");
        std::for_each(data.begin(), data.end(),
                      [](Stroke s) { std::cout << (s.first) << " " << s.after_last << "\n"; });
    }
    CHECK_EQ((Strokes{Stroke{0, 1}, Stroke{4, 6}}), runs("X...XX."));
    {
        auto data = runs("X...XX.");
        std::for_each(data.begin(), data.end(),
                      [](Stroke s) { std::cout << (s.first) << " " << s.after_last << "\n"; });
    }
}
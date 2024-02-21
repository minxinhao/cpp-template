#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template <typename... Funcs> auto tabulate(Funcs... funcs)
{
    return [=](int start, int end, int step = 1) {
        std::ostringstream oss;
        for (int i = start; i <= end; i += step)
        {
            ((oss << funcs(i)), ...);
            oss << '\n';
        }
        return oss.str();
    };
}

auto product = [](auto... fs) {
    return [&](auto... is) {
        auto rowf = [&is...](auto f) { return (f(is) + ...); };
        return (rowf(fs) + ...);
    };
};

int main()
{
    auto combinedFunc =
        product([](auto i) { return i; }, [](auto i) { return i * i; }, [](auto i) { return i * i * i - 1; })(1,2,3);

    // std::string table = combinedFunc(1, 2, 3);

    std::cout << combinedFunc << std::endl;

    return 0;
}
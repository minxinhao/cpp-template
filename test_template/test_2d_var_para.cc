#include <iostream>
#include <sstream>
#include <string>
#include <vector>


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
#include <iostream>
#include <functional>
#include <tuple>

void foo(int a, int b) {
    std::cout << "foo: " << a << ", " << b << std::endl;
}

int main() {
    std::tuple<int, int> args(1, 2);

    std::apply(foo, args);  // 使用 std::apply
    foo(args);              // 直接调用

    return 0;
}
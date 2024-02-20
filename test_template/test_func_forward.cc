#include <iostream>
#include <optional>
#include <string>

struct MyType
{
    std::string data;

    MyType(const std::string &str) : data(str)
    {
        std::cout << "Copy constructor called." << std::endl;
    }

    MyType(std::string &&str) : data(std::move(str))
    {
        std::cout << "Move constructor called." << std::endl;
    }
};

std::optional<MyType> transform(std::optional<MyType> what, std::function<MyType(MyType)> function_T_to_R)
{
    if (!what.has_value())
        return std::nullopt;
    return function_T_to_R(std::move(what.value()));
}

MyType convert(const MyType &input)
{
    return MyType("Converted: " + input.data);
}

int main()
{
    MyType obj("Original");

    std::optional<MyType> optionalObj(obj);
    std::optional<MyType> transformedObj = transform(optionalObj, convert);

    return 0;
}
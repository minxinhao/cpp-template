#include <iostream>
#include <utility>

class Example
{
  public:
    Example()
    {
        std::cout << "Default constructor" << std::endl;
    }
    Example(const Example &)
    {
        std::cout << "Copy constructor" << std::endl;
    }
    Example(Example &&)
    {
        std::cout << "Move constructor" << std::endl;
    }

    Example &operator=(const Example &)
    {
        std::cout << "Copy assignment" << std::endl;
        return *this;
    }
    Example &operator=(const Example &&)
    {
        std::cout << "Move assignment" << std::endl;
        return *this;
    }
};

int main()
{
    Example obj1;
    Example obj2;

    std::cout << "Using std::exchange with left value:" << std::endl;
    Example old_value1 = std::exchange(obj1, obj2);

    std::cout << "Using std::exchange with right value:" << std::endl;
    Example old_value2 = std::exchange(obj1, Example());

    return 0;
}
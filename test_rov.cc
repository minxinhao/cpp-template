#include <iostream>

class MyObject {
public:
    MyObject() {
        std::cout << "Default constructor called" << std::endl;
    }

    MyObject(const MyObject& other) {
        std::cout << "Copy constructor called" << std::endl;
    }
};

MyObject createObject() {
    return MyObject();
}

int main() {
    MyObject obj = createObject();
    MyObject obj2(obj);
    return 0;
}
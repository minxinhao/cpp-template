#include<iostream>

template<class T>
struct X {
    void f()const { std::cout << "X\n"; }
};

void f() { std::cout << "全局\n"; }

template<class T>
struct Y : X<T> {
    void t()const {
        this->f();
    }
    void t2()const {
        f();
    }
};

int main() {
    Y<void>y;
    y.t();
    y.t2();
}
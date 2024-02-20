#pragma once

#include <algorithm>
#include <array>

struct Heavy
{
    int *data = nullptr;
    size_t size = 0;
    Heavy()
    {
    }
    explicit Heavy(int size) : data(new int[size]), size(size)
    {
    }
    Heavy(const Heavy &other) : data(new int[other.size]), size(other.size)
    {
    }
    Heavy(Heavy &&other) : data(other.data), size(other.size)
    {
        other.data = nullptr;
        other.size = 0;
    }
    Heavy &operator=(const Heavy &other)
    {
        data = new int[other.size];
        size = other.size;
        return *this;
    }
    Heavy &operator=(Heavy &&other)
    {
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        return *this;
    }

    ~Heavy()
    {
        delete[] data;
    }
};

class Consumer
{
  public:
    // TODO: tweak this constant to make your test fail
    // (the moveable_objects tests)
    static constexpr size_t size = 100;

    Consumer(std::array<Heavy, size> prototype);
    static void access(std::array<Heavy, size> &);

  private:
    std::array<Heavy, size> member;
};
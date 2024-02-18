#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "docktest.h"
#include <algorithm>
#include <array>

namespace
{
class file_guard
{
  public:
    file_guard(const char *__filename, const char *__mode) : f(nullptr)
    {
        // check filename exis
        f = fopen(__filename, __mode);
        if (f == nullptr)
            fclose(f);
    }
    ~file_guard()
    {
        if (f != nullptr)
            fclose(f);
        f = nullptr;
    }

    void do_stuff()
    {
        MESSAGE("doing...");
    }

  private:
    FILE *f;
};

void do_stuff_with(FILE *f)
{
}
} // namespace

TEST_CASE("RAII, DISABLED_objectsCanBeCleantAtDestructionTime")
{
    // TODO: make this bunch of code _not_ leak
    // resources
    //
    // write a class to wrap it,
    // or less generic: use an std class
    // FILE *f = fopen("file", "w+");
    // do_stuff_with(f);
    file_guard file("file", "w+");
    file.do_stuff();
}

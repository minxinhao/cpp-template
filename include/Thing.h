#pragma once

#include <string>

// ... imagine a huge class hierarchy
class Thing
{
  public:
    virtual ~Thing()
    {
    }

    Thing(std::string name) : thing_name(std::move(name))
    {
    }

    virtual double size_in_cm() const
    // TODO: just change the method name
    // and make sure the derived classes don't accidentally
    // compile.
    // virtual double size_in_m() const
    {
        throw std::logic_error("not implemented");
    }

    virtual std::string purpose() const = 0;

    virtual std::string name() const
    {
        return "just a thing";
    }

  private:
    std::string thing_name;
};
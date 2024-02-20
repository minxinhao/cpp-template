#pragma once

#include "Thing.h"

class Instrument : public Thing
{
  public:
    using Thing::Thing;
    virtual std::string purpose() const
    {
        return "making music";
    }
};
#pragma once

#include "Vehicle.h"

class MyBike : public Vehicle
{
  public:
    using Vehicle::Vehicle;

    std::string purpose() const override
    {
        return "transporting";
    }

    virtual int horse_power() const override
    {
        return 1;
    }

    virtual double size_in_cm() const override
    {
        return 60.0;
    }
};
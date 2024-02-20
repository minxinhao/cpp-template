#include "Instrument.h"

class Piano : public Instrument
{
  public:
    using Instrument::Instrument;

    virtual double size_in_cm() const override
    {
        return 130;
    }

    virtual std::string name() const override
    {
        return "my piano";
    }

    Piano &operator=(const Piano &other) = default;
};

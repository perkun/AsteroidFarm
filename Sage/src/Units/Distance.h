#pragma once

#include "Units.h"

namespace Sage {

template <Factor_t Factor>
using Distance = Unit<Dimension::Length, Factor>;

namespace UnitLiterals {

// TODO move to .cpp
auto operator"" _m(long double val)
{
    return Distance<Units::Meter>::cast(val);
}

// TODO move to .cpp
auto operator"" _mi(long double val)
{
    return Distance<Units::Mile>::cast(val);
}

}  // namespace UnitLiterals

}  // namespace Sage

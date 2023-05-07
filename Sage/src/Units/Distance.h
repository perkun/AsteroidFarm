#pragma once

#include "Units.h"

namespace Sage {

namespace Units {
constexpr Factor_t Meter{1.0};
constexpr Factor_t Mile{1609.344};

}  // namespace Units

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

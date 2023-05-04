#pragma once

#include "Units.h"

namespace Sage {

namespace Units {
constexpr double Meter = 1.0;
constexpr double Mile = 1609.344;

}  // namespace Units

template <double Factor>
using Distance = Unit<Dimension::Length, Factor>;

namespace UnitLiterals {

auto operator"" _m(long double val)
{
    return Distance<Units::Meter>::cast(val);
}

auto operator"" _mi(long double val)
{
    return Distance<Units::Mile>::cast(val);
}

}  // namespace UnitLiterals

}  // namespace Sage

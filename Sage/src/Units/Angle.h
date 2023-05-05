#pragma once

#include "Units.h"

namespace Sage {

namespace Units {
constexpr double PiVal = 3.141592653589793238462643383279502884197169399375L;
constexpr double Degree = PiVal / 180.0;
constexpr double Radian = 1.0;
}  // namespace Units

template <double Factor>
using Angle = Unit<Dimension::Angle, Factor>;

namespace UnitLiterals {

Angle<Units::Radian> operator"" _rad(long double val);
Angle<Units::Radian> operator"" _rad(unsigned long long int val);
Angle<Units::Degree> operator"" _deg(long double val);
Angle<Units::Degree> operator"" _deg(unsigned long long int val);

}  // namespace UnitLiterals

const auto Pi = Angle<Units::Radian>::cast(3.141592653589793238462643383279502884197169399375);
}  // namespace Sage
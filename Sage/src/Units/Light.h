#pragma once

#include "Units.h"

namespace Sage {

namespace Units {
constexpr Factor_t Mag{1.0};
}  // namespace Units

using Magnitude = Unit<Dimension::Light, Units::Mag>;

namespace UnitLiterals {
Magnitude operator""_mag(long double val);
Magnitude operator""_mag(unsigned long long int val);
}  // namespace UnitLiterals

}  // namespace Sage

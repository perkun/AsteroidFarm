#pragma once

#include "Units.h"

namespace Sage {

using Magnitude = Unit<Dimension::Light, Units::Mag>;

namespace UnitLiterals {
Magnitude operator""_mag(long double val);
Magnitude operator""_mag(unsigned long long int val);
}  // namespace UnitLiterals

}  // namespace Sage

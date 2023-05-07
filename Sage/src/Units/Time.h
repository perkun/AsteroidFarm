#pragma once

#include "Units.h"

namespace Sage {

namespace Units {
constexpr Factor_t Day{1.0};
constexpr Factor_t Hour{1./24.0};
constexpr Factor_t Minute{1./ 24. / 60.};
constexpr Factor_t Second{1./ 24. / 3600.};
}  // namespace Units

template <Factor_t Factor>
using JulianDay = Unit<Dimension::Time, Factor>;

namespace UnitLiterals {

JulianDay<Units::Day> operator""_jd(long double val);
JulianDay<Units::Day> operator""_jd(unsigned long long int val);
JulianDay<Units::Hour> operator""_h(long double val);
JulianDay<Units::Hour> operator""_h(unsigned long long int val);
JulianDay<Units::Minute> operator""_min(long double val);
JulianDay<Units::Minute> operator""_min(unsigned long long int val);
JulianDay<Units::Second> operator""_sec(long double val);
JulianDay<Units::Second> operator""_sec(unsigned long long int val);

}  // namespace UnitLiterals

}  // namespace Sage

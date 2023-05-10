#include "Units.h"

namespace Sage::UnitsLiterals {

Angle<Units::Radian> operator"" _rad(long double val)
{
    return Angle<Units::Radian>::cast(val);
}

Angle<Units::Radian> operator"" _rad(unsigned long long int val)
{
    return Angle<Units::Radian>::cast(static_cast<long double>(val));
}

Angle<Units::Degree> operator"" _deg(long double val)
{
    return Angle<Units::Degree>::cast(val);
}

Angle<Units::Degree> operator"" _deg(unsigned long long int val)
{
    return Angle<Units::Degree>::cast(val);
}

JulianDay<Units::Day> operator""_jd(long double val)
{
    return JulianDay<Units::Day>::cast(val);
}

JulianDay<Units::Day> operator""_jd(unsigned long long int val)
{
    return JulianDay<Units::Day>::cast(val);
}

JulianDay<Units::Hour> operator""_h(long double val)
{
    return JulianDay<Units::Hour>::cast(val);
}

JulianDay<Units::Hour> operator""_h(unsigned long long int val)
{
    return JulianDay<Units::Hour>::cast(val);
}

JulianDay<Units::Minute> operator""_min(long double val)
{
    return JulianDay<Units::Minute>::cast(val);
}

JulianDay<Units::Minute> operator""_min(unsigned long long int val)
{
    return JulianDay<Units::Minute>::cast(val);
}

JulianDay<Units::Second> operator""_sec(long double val)
{
    return JulianDay<Units::Second>::cast(val);
}

JulianDay<Units::Second> operator""_sec(unsigned long long int val)
{
    return JulianDay<Units::Second>::cast(val);
}

Distance<Units::Meter> operator"" _m(long double val)
{
    return Distance<Units::Meter>::cast(val);
}

Distance<Units::Meter> operator"" _mi(long double val)
{
    return Distance<Units::Mile>::cast(val);
}

Magnitude operator""_mag(long double val)
{
    return Magnitude::cast(val);
}
Magnitude operator""_mag(unsigned long long int val)
{
    return Magnitude::cast(val);
}

}  // namespace Sage::UnitsLiterals

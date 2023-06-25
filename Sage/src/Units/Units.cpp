#include "Units.h"

namespace Sage::UnitLiterals {

Angle<Units::Radian> operator""_rad(long double val)
{
    return Angle<Units::Radian>::cast(val);
}

Angle<Units::Radian> operator""_rad(unsigned long long int val)
{
    return Angle<Units::Radian>::cast(static_cast<long double>(val));
}

Angle<Units::Degree> operator""_deg(long double val)
{
    return Angle<Units::Degree>::cast(val);
}

Angle<Units::Degree> operator""_deg(unsigned long long int val)
{
    return Angle<Units::Degree>::cast(val);
}

Duration<Units::Hour> operator""_h(long double val)
{
    return Duration<Units::Hour>::cast(val);
}

Duration<Units::Hour> operator""_h(unsigned long long int val)
{
    return Duration<Units::Hour>::cast(val);
}

Duration<Units::Minute> operator""_min(long double val)
{
    return Duration<Units::Minute>::cast(val);
}

Duration<Units::Minute> operator""_min(unsigned long long int val)
{
    return Duration<Units::Minute>::cast(val);
}

Duration<Units::Second> operator""_sec(long double val)
{
    return Duration<Units::Second>::cast(val);
}

Duration<Units::Second> operator""_sec(unsigned long long int val)
{
    return Duration<Units::Second>::cast(val);
}

Distance<Units::Meter> operator""_m(long double val)
{
    return Distance<Units::Meter>::cast(val);
}

Distance<Units::Mile> operator""_mi(long double val)
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

}  // namespace Sage::UnitLiterals

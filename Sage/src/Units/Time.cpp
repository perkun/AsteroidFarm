#include "Time.h"

namespace Sage {

namespace UnitLiterals {

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

JulianDay<Units::Hour>operator""_h(unsigned long long int val)
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

}  // namespace UnitLiterals

} //

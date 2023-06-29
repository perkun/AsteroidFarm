#include "JulianDay.h"

namespace AsteroidFarm {

JulianDay::JulianDay(double jd) : _value(jd) {}

double JulianDay::value() const
{
    return _value;
}

Duration<Units::Day> operator-(const JulianDay &lhs, const JulianDay &rhs)
{
    return Duration<Units::Day>::cast(lhs.value() - rhs.value());
}

std::ostream &operator<<(std::ostream &out, const JulianDay &jd)
{
    return out << jd.value();
}

void from_json(const nlohmann::json &j, JulianDay &jd)
{
    jd = j.get<double>();
}

void to_json(nlohmann::json &j, const JulianDay &jd)
{
    j = jd.value();
}

namespace UnitLiterals {

JulianDay operator""_jd(long double val)
{
    return JulianDay(val);
}

JulianDay operator""_jd(unsigned long long int val)
{
    return JulianDay(val);
}

}  // namespace UnitLiterals

}  // namespace AsteroidFarm

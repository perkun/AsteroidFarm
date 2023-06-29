#pragma once

#include "Units.h"

namespace AsteroidFarm {

// NOTE something like time_point
class JulianDay
{
public:
    JulianDay() = default;
    JulianDay(double jd);

    double value() const;

    friend Duration<Units::Day> operator-(const JulianDay &lhs, const JulianDay &rhs);

    friend bool operator==(const JulianDay &lhs, const JulianDay &rhs)
    {
        return lhs.value() == rhs.value();
    }

    template <Factor_t Factor>
    JulianDay &operator-=(const Duration<Factor> &duration)
    {
        Duration<Units::Day> d = duration;
        _value -= d.value();
        return *this;
    }

    template <Factor_t Factor>
    friend JulianDay operator-(JulianDay jd, const Duration<Factor> &duration)
    {
        jd -= duration;
        return jd;
    }

    template <Factor_t Factor>
    JulianDay &operator+=(const Duration<Factor> &duration)
    {
        Duration<Units::Day> d = duration;
        _value += d.value();
        return *this;
    }

    template <Factor_t Factor>
    friend JulianDay operator+(JulianDay jd, const Duration<Factor> &duration)
    {
        jd += duration;
        return jd;
    }

private:
    double _value{0.};
};

std::ostream &operator<<(std::ostream &out, const JulianDay &jd);

void from_json(const nlohmann::json &j, JulianDay &jd);
void to_json(nlohmann::json &j, const JulianDay &jd);

namespace UnitLiterals {

JulianDay operator""_jd(long double val);
JulianDay operator""_jd(unsigned long long int val);

}

}  // namespace AsteroidFarm

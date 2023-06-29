#pragma once

#include <nlohmann/json.hpp>

namespace AsteroidFarm {

enum class Dimension
{
    Angle,
    Length,
    Time,
    Mass,
    Light,
};

template <Dimension DimensionId>
struct Factor_t
{
    double factor;
    static constexpr Dimension dimension{DimensionId};

    friend double operator*(Factor_t lhs, const Factor_t &rhs)
    {
        return lhs.factor * rhs.factor;
    }
    friend double operator/(Factor_t lhs, const Factor_t &rhs)
    {
        return lhs.factor / rhs.factor;
    }

    template <Dimension OtherDimensionId>
    friend constexpr bool operator==(const Factor_t<DimensionId> &lhs,
                                     const Factor_t<OtherDimensionId> &rhs)
    {
        return std::is_same<decltype(lhs), decltype(rhs)>::value && lhs.factor == rhs.factor;
    }
};

namespace Units {
constexpr double PiVal = 3.141592653589793238462643383279502884197169399375L;
constexpr Factor_t<Dimension::Angle> Degree{PiVal / 180.0};
constexpr Factor_t<Dimension::Angle> Radian{1.0};

constexpr Factor_t<Dimension::Length> Meter{1.0};
constexpr Factor_t<Dimension::Length> Mile{1609.344};

constexpr Factor_t<Dimension::Time> Day{1.0};
constexpr Factor_t<Dimension::Time> Hour{1. / 24.0};
constexpr Factor_t<Dimension::Time> Minute{1. / 24. / 60.};
constexpr Factor_t<Dimension::Time> Second{1. / 24. / 3600.};

constexpr Factor_t<Dimension::Light> Mag{1.0};
}  // namespace Units

template <Dimension DimensionId, Factor_t Factor>
class Unit
{
    static_assert(Factor.dimension == DimensionId, "Units have to be of apropriate dimension.");

public:
    constexpr static Unit cast(double val)
    {
        return {val};
    }

    Unit() = default;

    template <Factor_t OtherFactor>
    Unit(const Unit<DimensionId, OtherFactor> &other) : _value(OtherFactor / Factor * other.value())
    {}

    template <Factor_t OtherFactor>
    Unit &operator=(const Unit<DimensionId, OtherFactor> &other)
    {
        _value = OtherFactor / Factor * other.value();
        return *this;
    }

    double value() const
    {
        return _value;
    }

    Unit &operator*=(const double rhs)
    {
        _value *= rhs;
        return *this;
    }

    friend Unit operator*(Unit lhs, double rhs)
    {
        return lhs *= rhs;
    }

    friend Unit operator*(double lhs, Unit rhs)
    {
        return rhs *= lhs;
    }

    Unit &operator/=(const double rhs)
    {
        _value /= rhs;
        return *this;
    }

    friend Unit operator/(Unit lhs, double rhs)
    {
        return lhs /= rhs;
    }

    friend Unit operator/(double lhs, Unit rhs)
    {
        return rhs /= lhs;
    }

    // Unitless
    double &operator/=(const Unit &rhs)
    {
        return _value /= rhs.value();
    }

    template <Factor_t OtherFactor>
    friend double operator/(Unit lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        Unit rhsConv{rhs};
        return lhs /= rhsConv;
    }

    template <Factor_t OtherFactor>
    Unit &operator+=(const Unit<DimensionId, OtherFactor> &rhs)
    {
        _value += OtherFactor / Factor * rhs.value();
        return *this;
    }

    template <Factor_t OtherFactor>
    friend Unit operator+(Unit lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    template <Factor_t OtherFactor>
    Unit &operator-=(const Unit<DimensionId, OtherFactor> &rhs)
    {
        _value -= OtherFactor / Factor * rhs.value();
        return *this;
    }

    Unit operator-() const
    {
        return cast(-_value);
    }

    template <Factor_t OtherFactor>
    friend Unit operator-(Unit lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    template <Factor_t OtherFactor>
    friend bool operator<(const Unit &lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        return lhs.value() < OtherFactor / Factor * rhs.value();
    }

    template <Factor_t OtherFactor>
    friend bool operator>(const Unit &lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        return rhs < lhs;
    }

    template <Factor_t OtherFactor>
    friend bool operator<=(const Unit &lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        return ! (lhs > rhs);
    }

    template <Factor_t OtherFactor>
    friend bool operator>=(const Unit &lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        return ! (lhs < rhs);
    }

private:
    Unit(const long double val) : _value(val) {}

    double _value{0.};
};

template <Dimension DimensionId, Factor_t Factor1, Factor_t Factor2>
bool operator==(const Unit<DimensionId, Factor1> &lhs, const Unit<DimensionId, Factor2> &rhs)
{
    return lhs.value() == Factor2 / Factor1 * rhs.value();
}

template <Dimension DimensionId, Factor_t Factor>
std::ostream &operator<<(std::ostream &out, const Unit<DimensionId, Factor> &u)
{
    return out << u.value();
}

template <Dimension DimensionId, Factor_t Factor>
void from_json(const nlohmann::json &j, Unit<DimensionId, Factor> &u)
{
    u = Unit<DimensionId, Factor>::cast(j.get<double>());
}

template <Dimension DimensionId, Factor_t Factor>
void to_json(nlohmann::json &j, const Unit<DimensionId, Factor> &u)
{
    j = u.value();
}

// Specializations:

template <Factor_t Factor>
using Angle = Unit<Dimension::Angle, Factor>;
const auto Pi = Angle<Units::Radian>::cast(3.141592653589793238462643383279502884197169399375);

template <Factor_t Factor>
using Duration = Unit<Dimension::Time, Factor>;

template <Factor_t Factor>
using Distance = Unit<Dimension::Length, Factor>;

using Magnitude = Unit<Dimension::Light, Units::Mag>;

namespace UnitLiterals {

Angle<Units::Radian> operator""_rad(long double val);
Angle<Units::Radian> operator""_rad(unsigned long long int val);
Angle<Units::Degree> operator""_deg(long double val);
Angle<Units::Degree> operator""_deg(unsigned long long int val);

Duration<Units::Hour> operator""_h(long double val);
Duration<Units::Hour> operator""_h(unsigned long long int val);
Duration<Units::Minute> operator""_min(long double val);
Duration<Units::Minute> operator""_min(unsigned long long int val);
Duration<Units::Second> operator""_sec(long double val);
Duration<Units::Second> operator""_sec(unsigned long long int val);

Distance<Units::Meter> operator""_m(long double val);
Distance<Units::Mile> operator""_mi(long double val);

Magnitude operator""_mag(long double val);
Magnitude operator""_mag(unsigned long long int val);

}

}  // namespace AsteroidFarm

#pragma once

#include <nlohmann/json.hpp>

namespace Sage {

enum class Dimension
{
    Angle,
    Length,
    Time,
    Mass,
    Light,
};

template <Dimension DimensionId, double Factor>
class Unit
{
public:
    constexpr static Unit cast(double val)
    {
        return {val};
    }

    Unit() = default;

    template <double OtherFactor>
    Unit(const Unit<DimensionId, OtherFactor> &other) : _value(OtherFactor / Factor * other.value())
    {}

    template <double OtherFactor>
    Unit &operator=(const Unit<DimensionId, OtherFactor> &other)
    {
        // TODO
        // if (this == &other)
        //{
        //	return *this;
        //}

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

    template <double OtherFactor>
    friend double operator/(Unit lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        Unit rhsConv{rhs};
        return lhs /= rhsConv;
    }

    template <double OtherFactor>
    Unit &operator+=(const Unit<DimensionId, OtherFactor> &rhs)
    {
        _value += OtherFactor / Factor * rhs.value();
        return *this;
    }

    template <double OtherFactor>
    friend Unit operator+(Unit lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    template <double OtherFactor>
    Unit &operator-=(const Unit<DimensionId, OtherFactor> &rhs)
    {
        _value -= OtherFactor / Factor * rhs.value();
        return *this;
    }

    Unit operator-() const
    {
        return cast(-_value);
    }

    template <double OtherFactor>
    friend Unit operator-(Unit lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    template <double OtherFactor>
    friend bool operator<(const Unit &lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        return lhs.value() < OtherFactor / Factor * rhs.value();
    }

    template <double OtherFactor>
    friend bool operator>(const Unit &lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        return rhs < lhs;
    }

    template <double OtherFactor>
    friend bool operator<=(const Unit &lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        return !(lhs > rhs);
    }

    template <double OtherFactor>
    friend bool operator>=(const Unit &lhs, const Unit<DimensionId, OtherFactor> &rhs)
    {
        return !(lhs < rhs);
    }


private:
    Unit(const long double val) : _value(val) {}

    double _value{0.};
};

template <Dimension DimensionId, double Factor1, double Factor2>
bool operator==(const Unit<DimensionId, Factor1> &lhs, const Unit<DimensionId, Factor2> &rhs)
{
    return lhs.value() == Factor2 / Factor1 * rhs.value();
}

template <Dimension DimensionId, double Factor>
std::ostream& operator<<(std::ostream& out, const Unit<DimensionId, Factor> &u)
{
    return out << u.value();
}

template <Dimension DimensionId, double Factor>
void from_json(const nlohmann::json& j, Unit<DimensionId, Factor>& u)
{
    u = Unit<DimensionId, Factor>::cast(j.get<double>());
}

template <Dimension DimensionId, double Factor>
void to_json(nlohmann::json& j, const Unit<DimensionId, Factor>& u)
{
    j = u.value();
}


}  // namespace Sage
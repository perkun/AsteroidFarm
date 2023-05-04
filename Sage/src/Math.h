#pragma once

namespace Sage {

namespace Units
{
	constexpr double PiVal = 3.141592653589793238462643383279502884197169399375L;
	constexpr double Degree = PiVal / 180.0;
	constexpr double Radian = 1.0;

	constexpr double Meter = 1.0;
	constexpr double Mile = 1609.344;
} // namespace Units

enum class Dimension
{
	Angle,
	Length,
	Mass
};


template <Dimension DimensionId, double Factor>
class Unit
{
public:
	static Unit cast(double val)
	{
		return { val };
	}

	Unit() = default;

	template <double OtherFactor>
	Unit& operator=(const Unit<DimensionId, OtherFactor>& other)
	{
		// TODO
		//if (this == &other)
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


	Unit& operator*=(const double rhs)
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


	Unit& operator/=(const double rhs)
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


	template <double OtherFactor>
	Unit& operator+=(const Unit<DimensionId, OtherFactor>& rhs)
	{
		_value += OtherFactor / Factor * rhs.value();
		return *this;
	}

	template <double OtherFactor>
	friend Unit operator+(Unit lhs, Unit<DimensionId, OtherFactor>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <double OtherFactor>
	Unit& operator-=(const Unit<DimensionId, OtherFactor>& rhs)
	{
		_value += OtherFactor / Factor * rhs.value();
		return *this;
	}

	Unit operator-() const
	{
        return cast(-_value);
	}

	template <double OtherFactor>
	friend Unit operator-(Unit lhs, Unit<DimensionId, OtherFactor>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}



private:
	Unit(const long double val) : _value(val) {}

	double _value{0.};
};

template <Dimension DimensionId, double Factor1, double Factor2>
bool operator==(const Unit<DimensionId, Factor1>& lhs, const Unit<DimensionId, Factor2>& rhs)
{
	return lhs.value() == Factor2 / Factor1 * rhs.value();
}

template <double Factor>
using Angle = Unit<Dimension::Angle, Factor>;


namespace UnitLiterals {

auto operator"" _rad(long double val)
{
    return Angle<Units::Radian>::cast(val);
}

auto operator"" _rad(unsigned long long int val)
{
    return Angle<Units::Radian>::cast(static_cast<long double>(val));
}

auto operator"" _deg(long double val)
{
    return Angle<Units::Degree>::cast(val);
}

auto operator"" _deg(unsigned long long int val)
{
    return Angle<Units::Degree>::cast(val);
}

const auto Pi = 3.141592653589793238462643383279502884197169399375_rad;

template <double Factor>
using Distance = Unit<Dimension::Length, Factor>;

auto operator"" _m(long double val)
{
    return Distance<Units::Meter>::cast(val);
}

auto operator"" _mi(long double val)
{
    return Distance<Units::Mile>::cast(val);
}

} //


}  // namespace Sage::Math
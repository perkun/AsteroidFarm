#include <type_traits>
namespace Sage::Math {

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
	static Unit make(double val)
	{
		return { val };
	}

	// various literals
	friend Unit<Dimension::Angle, Units::Radian> operator ""_rad(long double);
	friend Unit<Dimension::Angle, Units::Radian> operator ""_rad(unsigned long long int);
	friend Unit<Dimension::Angle, Units::Degree> operator ""_deg(long double);
	friend Unit<Dimension::Angle, Units::Degree> operator ""_deg(unsigned long long int);

	friend Unit<Dimension::Length, Units::Meter> operator "" _m(long double val);
	friend Unit<Dimension::Length, Units::Mile> operator "" _mi(long double val);

public:
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


Angle<Units::Radian> operator "" _rad(long double val)
{
	return {val};
}

Angle<Units::Radian> operator "" _rad(unsigned long long int val)
{
	return {static_cast<long double>(val)};
}


Angle<Units::Degree> operator "" _deg(long double val)
{
	return Angle<Units::Degree>(val);
}

Angle<Units::Degree> operator "" _deg(unsigned long long int val)
{
	return Angle<Units::Degree>(val);
}

const auto Pi = 3.141592653589793238462643383279502884197169399375_rad;

template <double Factor>
using Distance = Unit<Dimension::Length, Factor>;

Distance<Units::Meter> operator "" _m(long double val)
{
	return Distance<Units::Meter>(val);
}

Distance<Units::Mile> operator "" _mi(long double val)
{
	return Distance<Units::Mile>(val);
}


}  // namespace Sage::Math
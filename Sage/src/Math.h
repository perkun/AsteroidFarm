#include <type_traits>
namespace Sage::Math {

template <double Factor>
class Angle
{
    double value() {return _value; }
private:
    double _value;
};

// sum of 2 angles
template <double Factor1, double Factor2>
constexpr Angle<Factor1> operator+(const Angle<Factor1> &lhs, const Angle<Factor2> &rhs)
{
    return {lhs.value() + (Factor1 / Factor2 * rhs.value())};
}

}  // namespace Sage::Math
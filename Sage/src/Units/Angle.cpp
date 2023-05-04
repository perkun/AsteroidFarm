#include "Angle.h"

namespace Sage {

namespace UnitLiterals {

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

}  // namespace UnitLiterals

} //
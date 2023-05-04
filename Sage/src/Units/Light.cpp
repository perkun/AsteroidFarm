#include "Light.h"

namespace Sage {

namespace UnitLiterals {
Magnitude operator""_mag(long double val)
{
    return Magnitude::cast(val);
}
Magnitude operator""_mag(unsigned long long int val)
{
    return Magnitude::cast(val);
}
}  // namespace UnitLiteral

}  // namespace Sage

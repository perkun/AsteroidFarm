#include <chrono>

namespace Sage {
// NOTE this is the difference between system's clock (Gregorian) epoch (00:00 1.01.1970)
// and 0 Julian day (12:00 24.12.-4713)
constexpr auto jdiff()
{
    using namespace std::chrono_literals;
    return std::chrono::duration<double, std::ratio<1>>(58574100 * 3600.);
}

struct jdate_clock;

struct jdate_clock
{
    using rep        = double;
    using period     = std::ratio<86400>;
    using duration   = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<jdate_clock>;

    static constexpr bool is_steady = false;

    static time_point now() noexcept
    {
        using namespace std::chrono;
        return time_point{duration{system_clock::now().time_since_epoch()} + jdiff()};
    }
};

template <class Duration>
constexpr auto sys_to_jdate(std::chrono::time_point<std::chrono::system_clock, Duration> tp) noexcept
{
    using namespace std::chrono;
    static_assert(jdate_clock::duration{jdiff()} < Duration::max(), "Overflow in sys_to_jdate");
    const auto d = tp.time_since_epoch() + jdiff();
    return time_point<jdate_clock, std::remove_cv_t<decltype(d)>>{d};
}

template <class Duration>
constexpr auto jdate_to_sys(std::chrono::time_point<jdate_clock, Duration> tp) noexcept
{
    using namespace std::chrono;
    static_assert(jdate_clock::duration{-jdiff()} > Duration::min(), "Overflow in jdate_to_sys");
    const auto d = tp.time_since_epoch() - jdiff();
    return time_point<system_clock, std::remove_cv_t<decltype(d)>>{d};
}

}  // namespace Sage
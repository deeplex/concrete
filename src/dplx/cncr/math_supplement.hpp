
// Copyright Henrik Steffen Gaßmann 2021-2022
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <concepts>
#include <limits>
#include <type_traits>

#include <dplx/cncr/concepts.hpp>

namespace dplx::cncr
{

template <typename T>
concept integer = std::integral<T>
                  && none_of<std::remove_cv_t<T>,
                             bool,
                             char,
                             wchar_t,
                             char8_t,
                             char16_t,
                             char32_t>;

template <typename T>
concept signed_integer = integer<T> && std::signed_integral<T>;

template <typename T>
concept unsigned_integer = integer<T> && std::unsigned_integral<T>;

template <typename T>
concept iec559_floating_point
        = std::floating_point<T> && std::numeric_limits<T>::is_iec559;

} // namespace dplx::cncr

namespace dplx::cncr
{

template <signed_integer T, signed_integer U>
constexpr auto div_ceil(T const dividend, U const divisor) noexcept
        -> std::common_type_t<T, U>
{
    using common_type = std::common_type_t<T, U>;
    using ucommon_type = std::make_unsigned_t<common_type>;
    // negative division results will round towards zero, i.e.
    // they are already rounded correctly and we must not adjust them
    // the XORed "sign bits" will force signComp to be non negative
    // if the division result is non negative
    // assuming signed integers are implemented with two's complement
    // (which is guaranteed by C++20)
    auto const signComp = static_cast<common_type>(
            static_cast<ucommon_type>(static_cast<common_type>(dividend))
            ^ static_cast<ucommon_type>(static_cast<common_type>(divisor)));

    return static_cast<common_type>(
            dividend / divisor + (signComp >= 0 && dividend % divisor != 0));
}
template <unsigned_integer T, unsigned_integer U>
constexpr auto div_ceil(T const dividend, U const divisor) noexcept
        -> std::common_type_t<T, U>
{
    using common_type = std::common_type_t<T, U>;
    return static_cast<common_type>(dividend / divisor
                                    + (dividend % divisor != 0U));
}

template <integer T, integer U>
constexpr auto round_up(T const value, U const multiple) noexcept
        -> std::common_type_t<T, U>
{
    return static_cast<std::common_type_t<T, U>>(
            cncr::div_ceil<T, U>(value, multiple) * multiple);
}

template <unsigned_integer T, unsigned_integer U>
constexpr auto round_up_p2(T const value, U const powerOf2) noexcept
        -> std::common_type_t<T, U>
{
    using common_type = std::common_type_t<T, U>;
    return static_cast<common_type>(
            static_cast<common_type>(value + powerOf2 - 1U)
            & (common_type{} - powerOf2));
}

template <unsigned_integer T, unsigned_integer U>
constexpr auto round_down(T const value, U const multiple) noexcept
{
    return static_cast<std::common_type_t<T, U>>((value / multiple) * multiple);
}

template <unsigned_integer T, unsigned_integer U>
constexpr auto round_down_p2(T const value, U const powerOf2) noexcept
{
    using common_type = std::common_type_t<T, U>;
    return static_cast<common_type>(value & (common_type{} - powerOf2));
}

template <signed_integer T, signed_integer U>
constexpr auto mod(T const k, U const n) noexcept -> std::common_type_t<T, U>
{
    using common_type = std::common_type_t<T, U>;
    using ucommon_type = std::make_unsigned_t<common_type>;

    auto const r = k % n;

    auto const needsAdjustment = r < 0;
    auto const mask
            = ucommon_type{} - static_cast<ucommon_type>(needsAdjustment);
    auto const adjustment
            = static_cast<common_type>(mask & static_cast<ucommon_type>(n));

    return static_cast<common_type>(r + adjustment);
}
template <unsigned_integer T, unsigned_integer U>
constexpr auto mod(T const k, U const n) noexcept -> std::common_type_t<T, U>
{
    return static_cast<std::common_type_t<T, U>>(k % n);
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
constexpr auto upow(unsigned long long x, unsigned long long e) noexcept
        -> unsigned long long
{
    unsigned long long result = 1U;
    while (e != 0U)
    {
        if ((e & 1U) != 0U)
        {
            result *= x;
        }
        e >>= 1;
        x *= x;
    }
    return result;
}

} // namespace dplx::cncr

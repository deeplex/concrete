
// Copyright Henrik Steffen Gaßmann 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>

#include <array>
#include <exception>
#include <functional>
#include <iterator>
#include <type_traits>

namespace dplx::cncr
{
    template <typename T>
    constexpr auto div_ceil(T dividend, T divisor) noexcept -> T
    {
        static_assert(std::is_integral_v<T>);

        if constexpr (std::is_unsigned_v<T>)
        {
            return dividend / divisor + (dividend % divisor != 0);
        }
        else
        {
            using unsigned_t = std::make_unsigned_t<T>;
            // negative division results will round towards zero, i.e.
            // they are already rounded correctly and we must not adjust them
            // the XORed "sign bits" will force signComp to be non negative
            // if the division result is non negative
            // assuming signed integers are implemented with two's complement
            // (which is guaranteed by C++20)
            const auto signComp =
                static_cast<T>(static_cast<unsigned_t>(dividend) ^
                               static_cast<unsigned_t>(divisor));

            return dividend / divisor +
                   (signComp >= 0 && dividend % divisor != 0);
        }
    }
    template <typename T, typename U>
    constexpr auto div_ceil(T dividend, U divisor) noexcept
        -> std::common_type_t<T, U>
    {
        using common_type = std::common_type_t<T, U>;
        return cncr::div_ceil(static_cast<common_type>(dividend),
                              static_cast<common_type>(divisor));
    }

    template <typename T, typename U>
    constexpr auto mod(T k, U n) noexcept -> std::common_type_t<T, U>
    {
        assert(n > 0);

        const auto r = k % n;
        if constexpr (std::is_signed_v<T>)
        {
            using common_type = std::common_type_t<T, U>;
            using ucommon_type = std::make_unsigned_t<common_type>;

            const auto needsAdjustment = r < 0;
            const auto mask = -static_cast<ucommon_type>(needsAdjustment);
            const auto adjustment = static_cast<common_type>(mask & n);
            return r + adjustment;
        }
        else
        {
            return r;
        }
    }

    constexpr auto upow(std::uint64_t x, std::uint64_t e) noexcept
        -> std::uint64_t
    {
        std::uint64_t result = 1;
        while (e)
        {
            if (e & 1)
            {
                result *= x;
            }
            e >>= 1;
            x *= x;
        }
        return result;
    }

    template <typename... Ts>
    constexpr auto make_byte_array(Ts... ts) noexcept
        -> std::array<std::byte, sizeof...(Ts)>
    {
        static_assert((... && std::is_integral_v<Ts>));
        return {static_cast<std::byte>(ts)...};
    }

    constexpr auto is_null_byte(const std::byte value) noexcept -> bool
    {
        return value == std::byte{};
    }
    constexpr auto is_non_null_byte(const std::byte value) noexcept -> bool
    {
        return !is_null_byte(value);
    }

    namespace detail
    {
        template <typename R, typename Fn, std::size_t... is, typename... Args>
        constexpr auto sequence_init(Fn &&initFn, std::index_sequence<is...>,
                                     Args const &... args) -> R
        {
            // #cpp_version_ODR_violation
#if __cpp_lib_constexpr_functional >= 201907L
            return R{std::invoke(std::forward<Fn>(initFn), args..., is)...};
#else
            return R{initFn(args..., is)...};
#endif
        }
    } // namespace detail

    template <typename R, std::size_t N, typename Fn, typename... Args>
    constexpr auto sequence_init(Fn &&initFn, Args &&... args) -> R
    {
        return detail::sequence_init<R>(std::forward<Fn>(initFn),
                                        std::make_index_sequence<N>{}, args...);
    }

    template <typename R, typename Fn, typename... Args>
    constexpr auto sequence_init(Fn &&initFn, Args &&... args) -> R
    {
        return detail::sequence_init<R>(
            std::forward<Fn>(initFn),
            std::make_index_sequence<std::size(R{})>{}, args...);
    }

    // #cpp_version_ODR_violation
#if __cpp_lib_remove_cvref >= 201711L

    template <typename T>
    using remove_cvref = std::remove_cvref<T>;

    template <typename T>
    using remove_cvref_t = std::remove_cvref_t<T>;

#else

    template <typename T>
    struct remove_cvref
    {
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
    };

    template <typename T>
    using remove_cvref_t = typename remove_cvref<T>::type;

#endif
} // namespace dplx::cncr

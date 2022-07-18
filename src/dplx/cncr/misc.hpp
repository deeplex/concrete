
// Copyright Henrik Steffen Gaßmann 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <utility>

namespace dplx::cncr
{

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr auto to_underlying(Enum value) noexcept ->
        typename std::underlying_type<Enum>::type
{
    return static_cast<std::underlying_type_t<Enum>>(value);
}

template <std::size_t N, typename T>
consteval auto make_byte_array(std::initializer_list<T> vs, T dv) noexcept
        -> std::array<std::byte, N>
{
    std::array<std::byte, N> cx{};
    auto cxIt = std::begin(cx);
    auto const cxEnd = std::end(cx);
    for (auto it = vs.begin(), end = vs.end(); it != end; ++it, ++cxIt)
    {
        *cxIt = static_cast<std::byte>(*it);
    }
    for (; cxIt != cxEnd; ++cxIt)
    {
        *cxIt = static_cast<std::byte>(dv);
    }

    return cx;
}

inline constexpr struct is_null_byte_fn
{
    constexpr auto operator()(std::byte const value) const noexcept -> bool
    {
        return value == std::byte{};
    }
} is_null_byte{};

inline constexpr struct is_non_null_byte_fn
{
    constexpr auto operator()(std::byte const value) const noexcept -> bool
    {
        return value != std::byte{};
    }
} is_non_null_byte{};

namespace detail
{

template <typename>
struct sequence_init_impl;

template <std::size_t... Is>
struct sequence_init_impl<std::index_sequence<Is...>>
{
    template <typename R, typename Fn, typename... Args>
    static auto create(Fn &&initFn, Args &&...args) -> R
    {
        return R{std::invoke(std::forward<Fn>(initFn), args...,
                             std::integral_constant<std::size_t, Is>{})...};
    }
};

} // namespace detail

template <typename R, std::size_t N, typename Fn, typename... Args>
constexpr auto sequence_init(Fn &&initFn, Args &&...args) -> R
{
    return detail::sequence_init_impl<std::make_index_sequence<N>>::
            template create<R>(std::forward<Fn>(initFn), args...);
}

template <typename R, typename Fn, typename... Args>
constexpr auto sequence_init(Fn &&initFn, Args &&...args) -> R
{
    return detail::sequence_init_impl<std::make_index_sequence<std::size(
            R{})>>::template create<R>(std::forward<Fn>(initFn), args...);
}

} // namespace dplx::cncr

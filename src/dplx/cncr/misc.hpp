
// Copyright Henrik Steffen Gaßmann 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cstddef>
#include <cstdint>

#include <functional>
#include <type_traits>
#include <utility>

namespace dplx::cncr
{

template <typename... Ts>
constexpr auto make_byte_array(Ts... ts) noexcept
        -> std::array<std::byte, sizeof...(Ts)>
{
    static_assert((... && std::is_integral_v<Ts>));
    return {static_cast<std::byte>(ts)...};
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
        return R{std::invoke(std::forward<Fn>(initFn), args..., is)...};
    }
};

template <typename R, typename Fn, std::size_t... is, typename... Args>
constexpr auto
sequence_init(Fn &&initFn, std::index_sequence<is...>, Args const &...args) -> R
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
constexpr auto sequence_init(Fn &&initFn, Args &&...args) -> R
{
    return detail::sequence_init_impl<std::make_index_sequence<N>>::create<R>(
            std::forward<Fn>(initFn), args...);
}

template <typename R, typename Fn, typename... Args>
constexpr auto sequence_init(Fn &&initFn, Args &&...args) -> R
{
    return detail::sequence_init_impl<std::make_index_sequence<std::size(
            R{})>>::create<R>(std::forward<Fn>(initFn), args...);
}

} // namespace dplx::cncr

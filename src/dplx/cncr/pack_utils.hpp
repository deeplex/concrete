
// Copyright Henrik Steffen Gaßmann 2020, 2022.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>

namespace dplx::cncr::detail
{

template <typename T, typename U>
auto mp_value_to(U) -> T;

template <typename>
struct nth_param_type_impl;

template <std::size_t... Is>
struct nth_param_type_impl<std::index_sequence<Is...>>
{
    template <typename T>
    static auto
    deduce(decltype(detail::mp_value_to<void *, std::size_t>(Is))..., T *, ...)
            -> T;
};

struct discarder
{
    template <typename T>
    // NOLINTNEXTLINE(bugprone-forwarding-reference-overload)
    constexpr discarder(T &&) noexcept
    {
    }
};

template <typename>
struct nth_param_value_impl;

template <std::size_t... Is>
struct nth_param_value_impl<std::index_sequence<Is...>>
{
    template <typename T>
    static constexpr auto
    access(decltype(detail::mp_value_to<discarder, std::size_t>(Is))...,
           T &&t,
           ...) noexcept -> decltype(auto)
    {
        return static_cast<T &&>(t);
    }
};

} // namespace dplx::cncr::detail

namespace dplx::cncr
{

template <std::size_t N, typename... Params>
using nth_param_t =
        typename decltype(detail::nth_param_type_impl<
                          std::make_index_sequence<N>>::
                                  deduce(std::add_pointer_t<std::type_identity<
                                                 Params>>{}...))::type;

template <std::size_t N, decltype(auto)... Vs>
inline constexpr auto nth_param_v
        = detail::nth_param_value_impl<std::make_index_sequence<N>>::access(
                static_cast<decltype(Vs) &&>(Vs)...);

template <std::size_t N>
struct nth_param_fn
{
    template <typename... Ts>
    constexpr auto operator()(Ts &&...vs) const noexcept -> decltype(auto)
    {
        return detail::nth_param_value_impl<
                std::make_index_sequence<N>>::access(static_cast<Ts &&>(vs)...);
    }
};
template <std::size_t N>
inline constexpr nth_param_fn<N> nth_param{};

} // namespace dplx::cncr

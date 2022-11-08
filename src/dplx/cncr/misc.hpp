
// Copyright Henrik Steffen Gaßmann 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <type_traits>
#include <utility>

#include <dplx/cncr/mp_lite.hpp>
#include <dplx/cncr/utils.hpp>

namespace dplx::cncr
{

template <std::size_t N, typename T>
consteval auto make_byte_array(std::initializer_list<T> vs)
        -> std::array<std::byte, N>
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    std::array<std::byte, N> cx;
    auto *cxIt = cx.data();
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    auto const *const cxEnd = cxIt + N;

    for (auto &&v : vs)
    {
        // no bounds checking here due to the fact that the compiler is required
        // to flag it anyway during constant evaluation
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        *(cxIt++) = static_cast<std::byte>(v);
    }
    if (cxIt != cxEnd)
    {
        throw "less than N array values have specified; use the overload with "
              "an explicit default value if this is intended";
    }
    return cx;
}
template <std::size_t N, typename T>
consteval auto make_byte_array(std::initializer_list<T> vs, T dv) noexcept
        -> std::array<std::byte, N>
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    std::array<std::byte, N> cx;
    auto *cxIt = cx.data();
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    auto const *const cxEnd = cxIt + N;

    for (auto &&v : vs)
    {
        // no bounds checking here due to the fact that the compiler is required
        // to flag it anyway during constant evaluation
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        *(cxIt++) = static_cast<std::byte>(v);
    }
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (; cxIt != cxEnd; ++cxIt)
    {
        *cxIt = static_cast<std::byte>(dv);
    }

    return cx;
}

namespace detail
{

template <typename>
struct sequence_init_impl;

template <std::size_t... Is>
struct sequence_init_impl<std::index_sequence<Is...>>
{
    template <typename R, typename Fn, typename... Args>
    DPLX_ATTR_FORCE_INLINE static constexpr auto create(Fn &&initFn,
                                                        Args const &...args)
            -> R
    {
        return R{std::invoke(static_cast<Fn &&>(initFn), args...,
                             mp_size_t<Is>{})...};
    }
};

} // namespace detail

template <typename R, std::size_t N, typename Fn, typename... Args>
DPLX_ATTR_FORCE_INLINE constexpr auto sequence_init(Fn &&initFn,
                                                    Args const &...args) -> R
{
    using impl = detail::sequence_init_impl<std::make_index_sequence<N>>;

    return impl::template create<R, Fn &&, Args...>(static_cast<Fn &&>(initFn),
                                                    args...);
}

template <typename R, typename Fn, typename... Args>
DPLX_ATTR_FORCE_INLINE constexpr auto sequence_init(Fn &&initFn,
                                                    Args const &...args) -> R
{
    using impl = detail::sequence_init_impl<
            std::make_index_sequence<std::size(R{})>>;

    return impl::template create<R, Fn &&, Args...>(static_cast<Fn &&>(initFn),
                                                    args...);
}

} // namespace dplx::cncr


// Copyright Henrik Steffen Gaßmann 2020.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <iterator>
#include <ranges>
#include <type_traits>

namespace dplx::cncr
{

struct unreachable_sentinel
{
    template <std::weakly_incrementable It>
    friend constexpr auto operator==(It const &, unreachable_sentinel) noexcept
            -> bool
    {
        return false;
    }
};

template <std::input_or_output_iterator I>
using unbounded_range = std::ranges::
        subrange<I, unreachable_sentinel, std::ranges::subrange_kind::unsized>;

inline constexpr struct as_unbounded_range_fn
{
    template <std::input_or_output_iterator I>
    constexpr auto operator()(I it) const noexcept -> unbounded_range<I>
    {
        return unbounded_range<I>(it, unreachable_sentinel{});
    }

    template <std::ranges::borrowed_range R>
    constexpr auto operator()(R &&r) const noexcept
            -> unbounded_range<std::ranges::iterator_t<R>>
    {
        return unbounded_range<std::ranges::iterator_t<R>>(
                std::ranges::begin(r), unreachable_sentinel{});
    }

    template <typename T, std::size_t N>
    constexpr auto operator()(T (&arr)[N]) const noexcept
    {
        return unbounded_range<T *>(static_cast<T *>(arr),
                                    unreachable_sentinel{});
    }
} as_unbounded_range{};

} // namespace dplx::cncr

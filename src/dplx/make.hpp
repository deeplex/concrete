
// Copyright 2022-2023 Henrik Steffen Gaßmann
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <concepts>
#include <type_traits>

#include <dplx/cncr/disappointment.hpp>

namespace dplx
{

template <typename T>
struct make
{
};

// clang-format off
template <typename T>
concept makable
    = requires {
        typename T;
        typename make<T>;
    }                            
    && std::movable<T>
    && requires(make<T> const maker) {
        { maker() } noexcept -> cncr::tryable_result<T>;
    };
// clang-format on

} // namespace dplx

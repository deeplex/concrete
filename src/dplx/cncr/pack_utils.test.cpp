
// Copyright Henrik Steffen Gaßmann 2022
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/pack_utils.hpp"

#include <catch2/catch_test_macros.hpp>

#include "cncr_tests/test_utils.hpp"

namespace cncr_tests
{

static_assert(
        std::same_as<cncr::nth_param_t<0, int, unsigned, std::nullptr_t>, int>);
static_assert(std::same_as<cncr::nth_param_t<1, int, unsigned, std::nullptr_t>,
                           unsigned>);
static_assert(std::same_as<cncr::nth_param_t<2, int, unsigned, std::nullptr_t>,
                           std::nullptr_t>);

static_assert(cncr::nth_param_v<0, 1, 2U, std::byte{}> == 1);
static_assert(cncr::nth_param_v<1, 1, 2U, std::byte{}> == 2U);
static_assert(cncr::nth_param_v<2, 1, 2U, std::byte{}> == std::byte{});

static_assert(cncr::nth_param<0>(1, 2U, std::byte{}) == 1);
static_assert(cncr::nth_param<1>(1, 2U, std::byte{}) == 2U);
static_assert(cncr::nth_param<2>(1, 2U, std::byte{}) == std::byte{});

} // namespace cncr_tests

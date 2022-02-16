
// Copyright Henrik Steffen Gaßmann 2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/misc.hpp"
#include "dplx/cncr/mp_lite.hpp"

#include <catch2/catch.hpp>

#include "test_utils.hpp"

namespace cncr_tests
{

TEST_CASE("div_ceil")
{
    CHECK(cncr::div_ceil(-7, 7) == -1);
    CHECK(cncr::div_ceil(-6, 7) == 0);
    CHECK(cncr::div_ceil(0U, 7) == 0);
    CHECK(cncr::div_ceil(1U, 7) == 1);

    CHECK(cncr::div_ceil(19 * -1, 19) == -1);
    CHECK(cncr::div_ceil(19 * -1 + 1, 19) == 0);
    CHECK(cncr::div_ceil(19 * 0, 19) == 0);
    CHECK(cncr::div_ceil(19 * 0 + 1, 19) == 1);
    CHECK(cncr::div_ceil(19 * 1, 19) == 1);
    CHECK(cncr::div_ceil(19 * 1 + 1, 19) == 2);
    CHECK(cncr::div_ceil(19 * 2, 19) == 2);
    CHECK(cncr::div_ceil(19 * 2 + 1, 19) == 3);
}

TEST_CASE("mod")
{
    CHECK(cncr::mod(-5, 5) == 0);
    CHECK(cncr::mod(-4, 5) == 1);
    CHECK(cncr::mod(-1, 5) == 4);
    CHECK(cncr::mod(0, 5) == 0);
    CHECK(cncr::mod(1, 5) == 1);
    CHECK(cncr::mod(4, 5) == 4);
    CHECK(cncr::mod(5, 5) == 0);
    CHECK(cncr::mod(9, 5) == 4);
    CHECK(cncr::mod(10, 5) == 0);
}

} // namespace cncr_tests

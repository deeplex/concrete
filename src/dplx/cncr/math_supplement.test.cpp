
// Copyright Henrik Steffen Gaßmann 2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/math_supplement.hpp"

#include <catch2/catch_test_macros.hpp>

#include "cncr_tests/test_utils.hpp"

namespace cncr_tests
{

TEST_CASE("div_ceil/signed")
{
    CHECK(cncr::div_ceil(0, 7) == 0);
    CHECK(cncr::div_ceil(1, 7) == 1);
    CHECK(cncr::div_ceil(4, 7) == 1);
    CHECK(cncr::div_ceil(7, 7) == 1);
    CHECK(cncr::div_ceil(8, 7) == 2);

    CHECK(cncr::div_ceil(0, 7) == 0);
    CHECK(cncr::div_ceil(-1, 7) == 0);
    CHECK(cncr::div_ceil(-4, 7) == 0);
    CHECK(cncr::div_ceil(-6, 7) == 0);
    CHECK(cncr::div_ceil(-7, 7) == -1);

    CHECK(cncr::div_ceil(0, -7) == 0);
    CHECK(cncr::div_ceil(1, -7) == 0);
    CHECK(cncr::div_ceil(4, -7) == 0);
    CHECK(cncr::div_ceil(6, -7) == 0);
    CHECK(cncr::div_ceil(7, -7) == -1);

    CHECK(cncr::div_ceil(0, -7) == 0);
    CHECK(cncr::div_ceil(-1, -7) == 1);
    CHECK(cncr::div_ceil(-4, -7) == 1);
    CHECK(cncr::div_ceil(-7, -7) == 1);
    CHECK(cncr::div_ceil(-8, -7) == 2);

    CHECK(cncr::div_ceil(19 * -1, 19) == -1);
    CHECK(cncr::div_ceil(19 * -1 + 1, 19) == 0);
    CHECK(cncr::div_ceil(19 * 0, 19) == 0);
    CHECK(cncr::div_ceil(19 * 0 + 1, 19) == 1);
    CHECK(cncr::div_ceil(19 * 1, 19) == 1);
    CHECK(cncr::div_ceil(19 * 1 + 1, 19) == 2);
    CHECK(cncr::div_ceil(19 * 2, 19) == 2);
    CHECK(cncr::div_ceil(19 * 2 + 1, 19) == 3);
}

TEST_CASE("div_ceil/unsigned")
{
    CHECK(cncr::div_ceil(0U, 7U) == 0U);
    CHECK(cncr::div_ceil(1U, 7U) == 1U);
    CHECK(cncr::div_ceil(4U, 7U) == 1U);
    CHECK(cncr::div_ceil(7U, 7U) == 1U);
    CHECK(cncr::div_ceil(8U, 7U) == 2U);
}

TEST_CASE("round_up")
{
    CHECK(cncr::round_up(-6, 5) == -5);
    CHECK(cncr::round_up(-5, 5) == -5);
    CHECK(cncr::round_up(-4, 5) == 0);
}

TEST_CASE("mod/signed")
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

TEST_CASE("mod/unsigned")
{
    CHECK(cncr::mod(0U, 5U) == 0U);
    CHECK(cncr::mod(1U, 5U) == 1U);
    CHECK(cncr::mod(4U, 5U) == 4U);
    CHECK(cncr::mod(5U, 5U) == 0U);
    CHECK(cncr::mod(9U, 5U) == 4U);
    CHECK(cncr::mod(10U, 5U) == 0U);
}

} // namespace cncr_tests

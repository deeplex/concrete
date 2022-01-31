
// Copyright Henrik Steffen Gaßmann 2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/misc.hpp"

#include "boost-test.hpp"

using namespace dplx;

BOOST_AUTO_TEST_SUITE(misc_tests)

BOOST_AUTO_TEST_CASE(div_ceil_0)
{
    BOOST_TEST(cncr::div_ceil(-7, 7) == -1);
    BOOST_TEST(cncr::div_ceil(-6, 7) == 0);
    BOOST_TEST(cncr::div_ceil(0U, 7) == 0);
    BOOST_TEST(cncr::div_ceil(1U, 7) == 1);
}

BOOST_AUTO_TEST_CASE(div_ceil_boundary_19)
{
    BOOST_TEST(cncr::div_ceil(19 * -1, 19) == -1);
    BOOST_TEST(cncr::div_ceil(19 * -1 + 1, 19) == 0);
    BOOST_TEST(cncr::div_ceil(19 * 0, 19) == 0);
    BOOST_TEST(cncr::div_ceil(19 * 0 + 1, 19) == 1);
    BOOST_TEST(cncr::div_ceil(19 * 1, 19) == 1);
    BOOST_TEST(cncr::div_ceil(19 * 1 + 1, 19) == 2);
    BOOST_TEST(cncr::div_ceil(19 * 2, 19) == 2);
    BOOST_TEST(cncr::div_ceil(19 * 2 + 1, 19) == 3);
}

BOOST_AUTO_TEST_CASE(mod_5)
{
    BOOST_TEST(cncr::mod(-5, 5) == 0);
    BOOST_TEST(cncr::mod(-4, 5) == 1);
    BOOST_TEST(cncr::mod(-1, 5) == 4);
    BOOST_TEST(cncr::mod(0, 5) == 0);
    BOOST_TEST(cncr::mod(1, 5) == 1);
    BOOST_TEST(cncr::mod(4, 5) == 4);
    BOOST_TEST(cncr::mod(5, 5) == 0);
    BOOST_TEST(cncr::mod(9, 5) == 4);
    BOOST_TEST(cncr::mod(10, 5) == 0);
}

BOOST_AUTO_TEST_SUITE_END()

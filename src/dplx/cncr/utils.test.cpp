
// Copyright Henrik Steffen Gaßmann 2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/utils.hpp"

#include <catch2/catch_test_macros.hpp>

#include "cncr_tests/test_utils.hpp"

namespace cncr_tests
{

TEST_CASE("to_underlying maps correctly")
{
    enum class ttype : unsigned short
    {
        zero,
        one,
    };
    static_assert(std::same_as<decltype(cncr::to_underlying(ttype{})),
                               unsigned short>);

    CHECK(cncr::to_underlying(ttype::zero) == 0U);
    unsigned short underlying{cncr::to_underlying(ttype::one)};
    CHECK(underlying == 1U);
    CHECK(cncr::to_underlying(ttype{3U}) == 3U);
}

} // namespace cncr_tests

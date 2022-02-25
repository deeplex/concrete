
// Copyright Henrik Steffen Gaßmann 2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/misc.hpp"

#include <catch2/catch.hpp>

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
    unsigned short underlying = cncr::to_underlying(ttype::one);
    CHECK(underlying == 1U);
    CHECK(cncr::to_underlying(ttype{3U}) == 3U);
}

TEST_CASE("make byte array w/o default")
{
    auto const gen = cncr::make_byte_array<3>({2, 1, 0}, 0);
    REQUIRE(gen.size() == 3);
    CHECK(gen[0] == std::byte{2});
    CHECK(gen[1] == std::byte{1});
    CHECK(gen[2] == std::byte{0});
}

TEST_CASE("make byte array w default")
{
    auto const gen = cncr::make_byte_array<4>({2, 1}, 5);
    REQUIRE(gen.size() == 4);
    CHECK(gen[0] == std::byte{2});
    CHECK(gen[1] == std::byte{1});
    CHECK(gen[2] == std::byte{5});
    CHECK(gen[3] == std::byte{5});
}

} // namespace cncr_tests

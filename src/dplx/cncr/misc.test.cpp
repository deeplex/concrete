
// Copyright Henrik Steffen Gaßmann 2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/misc.hpp"

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

TEST_CASE("sequence init implicit simple")
{
    auto const gen = cncr::sequence_init<std::array<std::size_t, 5U>>(
            [](std::size_t b, std::size_t i) { return b + i; }, 3U);

    CHECK(gen[0] == 3U);
    CHECK(gen[1] == 4U);
    CHECK(gen[2] == 5U);
    CHECK(gen[3] == 6U);
    CHECK(gen[4] == 7U);
}

TEST_CASE("sequence init explicit simple")
{
    auto const gen = cncr::sequence_init<std::array<std::size_t, 5U>, 4U>(
            [](std::size_t b, std::size_t i) { return b + i; }, 3U);

    CHECK(gen[0] == 3U);
    CHECK(gen[1] == 4U);
    CHECK(gen[2] == 5U);
    CHECK(gen[3] == 6U);
    CHECK(gen[4] == 0U);
}

} // namespace cncr_tests

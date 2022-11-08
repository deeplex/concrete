
// Copyright Henrik Steffen Gaßmann 2019
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/ranges.hpp"

#include <array>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "cncr_tests/test_utils.hpp"

namespace cncr_tests
{

TEST_CASE("as_unbounded_range should work with pointers")
{
    std::array<int, 2> storage{};
    auto subject = cncr::as_unbounded_range(storage.data());
    static_assert(std::ranges::range<decltype(subject)>);
    CHECK(subject.begin() == storage.data());
}

TEST_CASE("as_unbounded_range should work with ranges")
{
    std::array<int, 2> storage{};
    auto subject = cncr::as_unbounded_range(storage);
    static_assert(std::ranges::range<decltype(subject)>);
    CHECK(subject.begin() == storage.begin());
}

TEST_CASE("as_unbounded_range should work with C arrays")
{
    int storage[2] = {};
    auto subject = cncr::as_unbounded_range(storage);
    static_assert(std::ranges::range<decltype(subject)>);
    CHECK(subject.begin() == std::ranges::begin(storage));
}

}


// Copyright Henrik Steffen Gaßmann 2022
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/tag_invoke.hpp"

#include <catch2/catch.hpp>

#include "cncr_tests/test_utils.hpp"

namespace cncr_tests
{

inline constexpr struct ti_test_cp_fn
{
    template <typename T>
        requires cncr::tag_invocable<ti_test_cp_fn, T &, std::size_t>
    constexpr decltype(auto) operator()(T &self, std::size_t n) const
    {
        return cncr::tag_invoke(*this, self, n);
    }
} ti_test_cp{};

struct ti_test_type
{
    std::size_t providedN{};
    bool called{};

    friend inline auto tag_invoke(ti_test_cp_fn, ti_test_type &self, std::size_t n)
            -> ti_test_type &
    {
        self.providedN = n;
        self.called = true;
        return self;
    }
};

TEST_CASE("tag_invoke should dispatch")
{
    ti_test_type testInstance;
    ti_test_type &testRef = ti_test_cp(testInstance, 13U);

    CHECK(testInstance.called);
    CHECK(testInstance.providedN == 13U);
    CHECK(&testInstance == &testRef);
}

} // namespace cncr_tests

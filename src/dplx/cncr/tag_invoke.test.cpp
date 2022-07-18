
// Copyright Henrik Steffen Gaßmann 2022
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/tag_invoke.hpp"

#include <catch2/catch_test_macros.hpp>

#include "cncr_tests/test_utils.hpp"

namespace cncr_tests
{

inline constexpr struct ti_test_cp_fn
{
    template <typename T>
        requires cncr::tag_invocable<ti_test_cp_fn, T &, std::size_t>
    constexpr auto operator()(T &self, std::size_t n) const -> decltype(auto)
    {
        return cncr::tag_invoke(*this, self, n);
    }
} ti_test_cp{};

struct ti_test_type
{
    std::size_t providedN{};
    bool called{};

    friend inline auto tag_invoke(ti_test_cp_fn,
                                  ti_test_type &self,
                                  std::size_t n) -> ti_test_type &
    {
        self.providedN = n;
        self.called = true;
        return self;
    }
};

} // namespace cncr_tests

namespace dplx::detail
{

// test tag_invoke poison pill
auto tag_invoke(cncr_tests::ti_test_cp_fn,
                cncr_tests::ti_test_type &self,
                std::size_t n) -> cncr_tests::ti_test_type &
{
    self.providedN = n;
    self.called = false;
    return self;
}

} // namespace dplx::detail

namespace dplx::cncr
{

struct ti_test_type
{
    std::size_t providedN{};
    bool called{};

    friend inline auto tag_invoke(cncr_tests::ti_test_cp_fn,
                                  ti_test_type &self,
                                  std::size_t n) -> ti_test_type &
    {
        self.providedN = n;
        self.called = true;
        return self;
    }
};

inline constexpr struct ti_test_cp_fn
{
    template <typename T>
        requires cncr::tag_invocable<ti_test_cp_fn, T &, std::size_t>
    constexpr auto operator()(T &self, std::size_t n) const -> decltype(auto)
    {
        return cncr::tag_invoke(*this, self, n);
    }
} ti_test_cp{};

// test tag_invoke definitions within dplx::cncr
auto tag_invoke(ti_test_cp_fn, cncr_tests::ti_test_type &self, std::size_t n)
        -> cncr_tests::ti_test_type &
{
    self.providedN = n;
    self.called = true;
    return self;
}

} // namespace dplx::cncr

namespace cncr_tests
{
TEST_CASE("tag_invoke should dispatch")
{
    ti_test_type testInstance;
    ti_test_type &testRef = ti_test_cp(testInstance, 13U);

    CHECK(testInstance.called);
    CHECK(testInstance.providedN == 13U);
    CHECK(&testInstance == &testRef);
}

TEST_CASE("tag_invoke should dispatch to cncr namespace declarations")
{
    ti_test_type testInstance;
    ti_test_type &testRef = cncr::ti_test_cp(testInstance, 13U);

    CHECK(testInstance.called);
    CHECK(testInstance.providedN == 13U);
    CHECK(&testInstance == &testRef);
}

} // namespace cncr_tests

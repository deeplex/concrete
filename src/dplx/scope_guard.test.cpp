
// Copyright Henrik Steffen Gaßmann 2022
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/scope_guard.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cncr_tests/test_utils.hpp>

namespace cncr_tests
{

TEST_CASE("scope_exit is constructible from a lambda rvalue")
{
    int called = 0;
    {
        scope_exit subject = [&called]
        {
            called += 1;
        };
    }

    CHECK(called == 1);
}

TEST_CASE("scope_exit is constructible from a lambda lvalue")
{
    auto exitFunction = [] {
    };
    scope_exit subject = exitFunction;
}

struct callable_noexcept_move
{
    int *called{nullptr};

    callable_noexcept_move() = default;
    callable_noexcept_move(callable_noexcept_move &&) noexcept = default;

    callable_noexcept_move(int *out) noexcept
        : called{out}
    {
    }

    void operator()() const noexcept
    {
        if (called != nullptr)
        {
            *called += 1;
        }
    }
};
static_assert(
        std::is_nothrow_constructible_v<scope_exit<callable_noexcept_move>,
                                        callable_noexcept_move>);

struct callable_throwing_copy
{
    int *called{nullptr};

    callable_throwing_copy() = default;
    callable_throwing_copy(callable_throwing_copy const &)
    {
    }

    callable_throwing_copy(int *out) noexcept
        : called{out}
    {
    }

    void operator()() const noexcept
    {
        if (called != nullptr)
        {
            *called += 1;
        }
    }
};

struct callable_throwing_move_with_copy
{
    int *called{nullptr};

    callable_throwing_move_with_copy() = default;
    callable_throwing_move_with_copy(
            callable_throwing_move_with_copy const &) noexcept
    {
    }
    // NOLINTNEXTLINE(performance-noexcept-move-constructor)
    callable_throwing_move_with_copy(callable_throwing_move_with_copy &&)
    {
    }

    callable_throwing_move_with_copy(int *out) noexcept
        : called{out}
    {
    }

    void operator()() const noexcept
    {
        if (called != nullptr)
        {
            *called += 1;
        }
    }
};
static_assert(std::is_nothrow_constructible_v<
              scope_exit<callable_throwing_move_with_copy>,
              callable_throwing_move_with_copy>);

TEST_CASE("scope_exit is constructible from a throwing rvalue move")
{
    scope_exit subject = callable_throwing_move_with_copy{};
}

TEST_CASE("scope_exit is constructible from a throwing rvalue copy")
{
    scope_exit subject = callable_throwing_copy{};
}

TEST_CASE("scope_exit is constructible from a throwing lvalue")
{
    callable_throwing_copy exitFunction{};
    scope_exit subject = exitFunction;
}

TEST_CASE("scope_exit can be moved and still executes once")
{
    int numCalls = 0;
    {
        scope_exit subject1 = callable_noexcept_move{&numCalls};
        scope_exit subject2 = std::move(subject1);
    }
    CHECK(numCalls == 1);
}

TEST_CASE("scope_exit::release cancels execution of the finalization logic")
{
    int numCalls = 0;
    {
        scope_exit subject = callable_noexcept_move{&numCalls};
        subject.release();
    }
    CHECK(numCalls == 0);
}

} // namespace cncr_tests

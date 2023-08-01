
// Copyright 2022-2023 Henrik Steffen Gaßmann
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/disappointment.hpp"

#include "test_utils.hpp"

namespace cncr_tests
{

namespace
{
struct rx_base
{
};
struct rx_derived : rx_base
{
};
} // namespace

static_assert(cncr::tryable<result<int>>);
static_assert(cncr::tryable<result<int *>>);
static_assert(cncr::tryable<result<char16_t>>);
static_assert(cncr::tryable<result<void>>);

static_assert(cncr::tryable_result<result<int>, int>);
static_assert(cncr::tryable_result<result<int>, long>);
static_assert(cncr::tryable_result<result<void>, void>);
static_assert(!cncr::tryable_result<result<void *>, int *>);
static_assert(!cncr::tryable_result<result<int>, int &>);
static_assert(cncr::tryable_result<result<int>, int const &>);
static_assert(cncr::tryable_result<result<int>, int &&>);
static_assert(cncr::tryable_result<result<rx_derived *>, rx_base *>);
static_assert(!cncr::tryable_result<result<rx_base *>, rx_derived *>);

static_assert(std::same_as<int, cncr::result_value_t<result<int>>>);
static_assert(std::same_as<void, cncr::result_value_t<result<void>>>);

static_assert(cncr::tryable<outcome::experimental::status_result<void>>);
static_assert(cncr::tryable<outcome::experimental::status_result<int>>);
static_assert(cncr::tryable<outcome::experimental::status_result<int *>>);

} // namespace cncr_tests

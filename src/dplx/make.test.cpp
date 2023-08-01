
// Copyright 2022-2023 Henrik Steffen Gaßmann
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/make.hpp"

#include "test_utils.hpp"

namespace cncr_tests
{

class myhandle
{
private:
    constexpr myhandle() noexcept = default;

public:
    static auto my() noexcept -> result<myhandle>
    {
        return myhandle{};
    }
};

} // namespace cncr_tests

template <>
struct dplx::make<cncr_tests::myhandle>
{
    auto operator()() const noexcept -> result<cncr_tests::myhandle>
    {
        return cncr_tests::myhandle::my();
    }
};

namespace cncr_tests
{

static_assert(makable<myhandle>);

}

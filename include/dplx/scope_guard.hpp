
// Copyright Henrik Steffen Gaßmann 2017
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <exception>
#include <utility>

namespace dplx
{

template <typename Fn>
struct scope_guard
{
    inline scope_guard(Fn &&fn)
        : mFn(std::forward<Fn>(fn))
    {
    }
    inline ~scope_guard() noexcept
    {
        mFn();
    }

private:
    Fn mFn;
};

template <typename Fn>
struct exception_scope_guard
{
    inline exception_scope_guard(Fn &&fn)
        : mFn(std::forward<Fn>(fn))
        , mUncaughtExceptions(std::uncaught_exceptions())
    {
    }
    inline ~exception_scope_guard() noexcept
    {
        if (mUncaughtExceptions < std::uncaught_exceptions())
        {
            mFn();
        }
    }

private:
    Fn mFn;
    int mUncaughtExceptions;
};

} // namespace dplx

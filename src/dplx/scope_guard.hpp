
// Copyright Henrik Steffen Gaßmann 2017
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <exception>
#include <type_traits>

namespace dplx
{

template <typename EF>
class scope_exit
{
    EF mExitFunction;
    bool mActive;

public:
    ~scope_exit()
    {
        if (mActive)
        {
            mExitFunction();
        }
    }

    scope_exit(scope_exit &&other) noexcept(
            std::is_nothrow_copy_constructible_v<EF>)
        : mExitFunction(other.mExitFunction)
        , mActive(other.mActive)
    {
        other.mActive = false;
    }
    scope_exit(scope_exit &&other) noexcept
        requires std::is_nothrow_move_constructible_v<EF>
        : mExitFunction(static_cast<EF &&>(other.mExitFunction))
        , mActive(other.mActive)
    {
        other.mActive = false;
    }

    // the following constructors defend against move confusion with constraints
    // NOLINTBEGIN(bugprone-forwarding-reference-overload)

    template <class Fn>
        requires(!std::is_same_v<std::remove_cvref_t<Fn>, scope_exit>)
                     && std::is_constructible_v<EF, Fn>
                     && std::is_nothrow_constructible_v<EF, Fn>
    scope_exit(Fn &&fn) noexcept
        : mExitFunction(static_cast<Fn &&>(fn))
        , mActive(true)
    {
    }
    template <class Fn>
        requires(!std::is_same_v<std::remove_cvref_t<Fn>, scope_exit>)
                     && std::is_constructible_v<EF, Fn>
                     && (!std::is_nothrow_constructible_v<EF, Fn>)
                     && std::is_nothrow_constructible_v<
                             EF,
                             std::remove_reference_t<Fn> &>
    scope_exit(Fn &&fn) noexcept
        : mExitFunction(fn)
        , mActive(true)
    {
    }
    template <class Fn>
        requires(!std::is_same_v<std::remove_cvref_t<Fn>, scope_exit>)
             && std::is_constructible_v<EF, Fn>
             && (!std::is_nothrow_constructible_v<EF, Fn>)
             && (!std::is_nothrow_constructible_v<
                     EF,
                     std::remove_reference_t<Fn> &>)
    scope_exit(Fn &&fn)
    try : mExitFunction(fn), mActive(true)
    {
    }
    catch (...)
    {
        fn();
        throw;
    }

    // NOLINTEND(bugprone-forwarding-reference-overload)

    void release() noexcept
    {
        mActive = false;
    }
};
template <class EF>
scope_exit(EF) -> scope_exit<EF>;

template <typename EF>
class scope_guard
{
    EF mExitFunction;

public:
    ~scope_guard()
    {
        mExitFunction();
    }

    // the following constructors defend against move confusion with constraints
    // NOLINTBEGIN(bugprone-forwarding-reference-overload)

    template <class Fn>
        requires(!std::is_same_v<std::remove_cvref_t<Fn>, scope_guard>)
             && std::is_constructible_v<EF, Fn>
             && std::is_nothrow_constructible_v<EF, Fn>
    scope_guard(Fn &&fn) noexcept
        : mExitFunction(static_cast<Fn &&>(fn))
    {
    }
    template <class Fn>
        requires(!std::is_same_v<std::remove_cvref_t<Fn>, scope_guard>)
             && std::is_constructible_v<EF, Fn>
             && (!std::is_nothrow_constructible_v<EF, Fn>)
             && std::is_nothrow_constructible_v<EF,
                                                std::remove_reference_t<Fn> &>
    scope_guard(Fn &&fn) noexcept
        : mExitFunction(fn)
    {
    }
    template <class Fn>
        requires(!std::is_same_v<std::remove_cvref_t<Fn>, scope_guard>)
             && std::is_constructible_v<EF, Fn>
             && (!std::is_nothrow_constructible_v<EF, Fn>)
             && (!std::is_nothrow_constructible_v<
                     EF,
                     std::remove_reference_t<Fn> &>)
    scope_guard(Fn &&fn)
    try : mExitFunction(fn)
    {
    }
    catch (...)
    {
        fn();
        throw;
    }

    // NOLINTEND(bugprone-forwarding-reference-overload)
};
template <class EF>
scope_guard(EF) -> scope_guard<EF>;

template <typename Fn>
    requires std::is_nothrow_move_constructible_v<Fn>
struct [[deprecated]] exception_scope_guard
{
    inline exception_scope_guard(Fn &&fn) noexcept
        : mFn(static_cast<Fn &&>(fn))
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

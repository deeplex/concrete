
// Copyright Henrik Steffen Gaßmann 2022
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/intrusive_ptr.hpp"

#include <catch2/catch_test_macros.hpp>
#include <dplx/cncr/workaround.h>
#include <dplx/predef/compiler.h>

#include "cncr_tests/test_utils.hpp"

namespace cncr_tests
{

class alien_ref_counted
{
    int mCounter{1};

public:
    void AddReference()
    {
        mCounter += 1;
    }
    void Release()
    {
        mCounter -= 1;
    }
};

} // namespace cncr_tests

template <>
struct dplx::cncr::reference_counted_traits<cncr_tests::alien_ref_counted>
{
    using counter_type = void;
    using ref_counted = cncr_tests::alien_ref_counted;

    static void add_reference(ref_counted &v) noexcept
    {
        v.AddReference();
    }

    static void release(ref_counted &v) noexcept
    {
        v.Release();
    }
};
#if DPLX_CNCR_WORKAROUND_TESTED_AT(DPLX_COMP_CLANG, 13, 0, 1)
// clang doesn't support disabling member functions with requires during
// explicit instantiation
#else
template class dplx::cncr::intrusive_ptr<cncr_tests::alien_ref_counted>;
#endif
static_assert(dplx::cncr::ref_counted<cncr_tests::alien_ref_counted>);
static_assert(
        !dplx::cncr::inspectable_ref_counted<cncr_tests::alien_ref_counted>);

namespace cncr_tests
{
class test_ref_counted
{
    mutable int mCounter{1};

public:
    constexpr void add_reference() const noexcept
    {
        mCounter += 1;
    }
    constexpr void release() const noexcept
    {
        mCounter -= 1;
    }
    constexpr auto reference_count() const noexcept -> int
    {
        return mCounter;
    }
};
static_assert(cncr::detail::dplx_ref_counted<test_ref_counted>);
static_assert(cncr::ref_counted<test_ref_counted>);

using test_intrusive_ptr = cncr::intrusive_ptr<test_ref_counted>;

TEST_CASE("intrusive_ptr should be default constructible and empty")
{
    test_intrusive_ptr ptr1;
    CHECK(!ptr1);

    test_intrusive_ptr ptr2{};
    CHECK(!ptr2);
}

TEST_CASE("intrusive_ptr can be initialized by a nullptr literal")
{
    test_intrusive_ptr ptr1(nullptr);
    CHECK(!ptr1);

    test_intrusive_ptr ptr2{nullptr};
    CHECK(!ptr2);

    test_intrusive_ptr ptr3 = nullptr;
    CHECK(!ptr3);
}

TEST_CASE("intrusive_ptr_acquire should create a intrusive_ptr and increase "
          "its reference count")
{
    test_ref_counted counted;

    auto subject = cncr::intrusive_ptr_acquire(&counted);

    CHECK(subject.get() == &counted);
    CHECK(counted.reference_count() == 2);
}
TEST_CASE("intrusive_ptr_acquire should create a intrusive_ptr from nullptr")
{
    test_ref_counted *null = nullptr;
    auto subject = cncr::intrusive_ptr_acquire(null);

    CHECK(!subject);
    CHECK(subject.get() == nullptr);
}

TEST_CASE("intrusive_ptr should call release() on the wrapped object on "
          "destruction")
{
    test_ref_counted counted;
    {
        auto subject = cncr::intrusive_ptr_import(&counted);

        CHECK(counted.reference_count() == 1);
    }
    CHECK(counted.reference_count() == 0);
}

TEST_CASE("intrusive_ptr_import should create a intrusive_ptr without "
          "increasing its reference count")
{
    test_ref_counted counted;
    auto subject = cncr::intrusive_ptr_import(&counted);

    CHECK(subject.get() == &counted);
    CHECK(counted.reference_count() == 1);
}
TEST_CASE("intrusive_ptr_import should create a intrusive_ptr from nullptr")
{
    test_ref_counted *null = nullptr;
    auto subject = cncr::intrusive_ptr_import(null);

    CHECK(!subject);
    CHECK(subject.get() == nullptr);
}

TEST_CASE("intrusive_ptr instance")
{
    test_ref_counted counted;
    auto subject = cncr::intrusive_ptr_import(&counted);
    REQUIRE(subject.get() == &counted);
    REQUIRE(counted.reference_count() == 1);

    SECTION("nullptr can be assigned to an instance")
    {
        subject = nullptr;

        CHECK(subject.get() == nullptr);
    }

    SECTION("should be copy constructible and add a new reference")
    {
        // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
        test_intrusive_ptr copy = subject;

        CHECK(subject.get() == &counted);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 2);
    }

    SECTION("should be copy assignable and add a new reference")
    {
        test_intrusive_ptr copy;
        auto &&assignmentResult = (copy = subject);

        CHECK(&assignmentResult == &copy);
        CHECK(subject.get() == &counted);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 2);
    }

    SECTION("should be move constructible avoiding a reference increment")
    {
        test_intrusive_ptr copy = std::move(subject);

        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
        CHECK(subject.get() == nullptr);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 1);
    }

    SECTION("should be move assignable avoiding a reference increment")
    {
        test_intrusive_ptr copy;
        auto &&assignmentResult = (copy = std::move(subject));

        CHECK(&assignmentResult == &copy);
        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
        CHECK(subject.get() == nullptr);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 1);
    }

    SECTION("should be swappable avoiding a reference increment")
    {
        test_intrusive_ptr copy;
        swap(subject, copy);

        CHECK(subject.get() == nullptr);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 1);
    }

    SECTION("reference_count() should return the reference count")
    {
        CHECK(subject.reference_count() == 1);
        counted.add_reference();
        CHECK(subject.reference_count() == 2);
    }
    SECTION("use_count() should return the reference count")
    {
        CHECK(subject.use_count() == 1);
        counted.add_reference();
        CHECK(subject.use_count() == 2);
    }

    SECTION("should provide an overloaded dereference operator")
    {
        CHECK(&(*subject) == &counted);
    }
    SECTION("should provide an overloaded member access operator")
    {
        CHECK(subject.operator->() == &counted);
    }

    SECTION("should provide a method to release ownership")
    {
        CHECK(subject.release() == &counted);
        CHECK(!subject);
        CHECK(counted.reference_count() == 1);
    }

    SECTION("should be convertible to intrusive_ptr<void>")
    {
        cncr::intrusive_ptr<void> copy = subject;

        CHECK(subject.get() == &counted);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 2);
    }
    SECTION("should be movable to intrusive_ptr<void>")
    {
        cncr::intrusive_ptr<void> copy = std::move(subject);

        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
        CHECK(subject.get() == nullptr);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 1);
    }
}

TEST_CASE("intrusive_ptr<void> should be default constructible and empty")
{
    cncr::intrusive_ptr<void> ptr1;
    CHECK(!ptr1);

    cncr::intrusive_ptr<void> ptr2{};
    CHECK(!ptr2);
}

TEST_CASE("intrusive_ptr<void> can be initialized by a nullptr literal")
{
    cncr::intrusive_ptr<void> ptr1(nullptr);
    CHECK(!ptr1);

    cncr::intrusive_ptr<void> ptr2{nullptr};
    CHECK(!ptr2);

    cncr::intrusive_ptr<void> ptr3 = nullptr;
    CHECK(!ptr3);
}
TEST_CASE("intrusive_ptr<void> can be initialized by an empty intrusive_ptr")
{
    test_intrusive_ptr input;

    cncr::intrusive_ptr<void> copied = input;
    CHECK(!copied);
    CHECK(copied.get() == nullptr);

    cncr::intrusive_ptr<void> moved = std::move(input);
    CHECK(!moved);
    CHECK(moved.get() == nullptr);
}

TEST_CASE("intrusive_ptr<void>::acquire should create a intrusive_ptr and "
          "increase its reference count")
{
    test_ref_counted counted;

    auto subject = cncr::intrusive_ptr<void>::acquire(&counted);

    CHECK(subject.get() == &counted);
    CHECK(counted.reference_count() == 2);
}
TEST_CASE("intrusive_ptr<void>::acquire should create a intrusive_ptr from "
          "nullptr")
{
    test_ref_counted *null = nullptr;
    auto subject = cncr::intrusive_ptr<void>::acquire(null);

    CHECK(!subject);
    CHECK(subject.get() == nullptr);
}

TEST_CASE("intrusive_ptr<void> should call release() on the wrapped object on "
          "destruction")
{
    test_ref_counted counted;
    {
        auto subject = cncr::intrusive_ptr<void>::import(&counted);

        CHECK(counted.reference_count() == 1);
    }
    CHECK(counted.reference_count() == 0);
}

TEST_CASE("intrusive_ptr<void>::import should create a intrusive_ptr without "
          "increasing its reference count")
{
    test_ref_counted counted;
    auto subject = cncr::intrusive_ptr<void>::import(&counted);

    CHECK(subject.get() == &counted);
    CHECK(counted.reference_count() == 1);
}
TEST_CASE("intrusive_ptr<void>::import should create a intrusive_ptr from "
          "nullptr")
{
    test_ref_counted *null = nullptr;
    auto subject = cncr::intrusive_ptr<void>::import(null);

    CHECK(!subject);
    CHECK(subject.get() == nullptr);
}

TEST_CASE("intrusive_ptr<void> instance")
{
    test_ref_counted counted;
    auto subject = cncr::intrusive_ptr<void>::import(&counted);
    REQUIRE(subject.get() == &counted);
    REQUIRE(counted.reference_count() == 1);

    SECTION("nullptr can be assigned to an instance")
    {
        subject = nullptr;

        CHECK(subject.get() == nullptr);
    }

    SECTION("should be copy constructible and add a new reference")
    {
        // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
        cncr::intrusive_ptr<void> copy = subject;

        CHECK(subject.get() == &counted);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 2);
    }

    SECTION("should be copy assignable and add a new reference")
    {
        cncr::intrusive_ptr<void> copy;
        auto &&assignmentResult = (copy = subject);

        CHECK(&assignmentResult == &copy);
        CHECK(subject.get() == &counted);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 2);
    }

    SECTION("should be move constructible avoiding a reference increment")
    {
        cncr::intrusive_ptr<void> copy = std::move(subject);

        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
        CHECK(subject.get() == nullptr);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 1);
    }

    SECTION("should be move assignable avoiding a reference increment")
    {
        cncr::intrusive_ptr<void> copy;
        auto &&assignmentResult = (copy = std::move(subject));

        CHECK(&assignmentResult == &copy);
        // NOLINTNEXTLINE(clang-analyzer-cplusplus.Move,bugprone-use-after-move)
        CHECK(subject.get() == nullptr);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 1);
    }

    SECTION("should be swappable avoiding a reference increment")
    {
        cncr::intrusive_ptr<void> copy;
        swap(subject, copy);

        CHECK(subject.get() == nullptr);
        CHECK(copy.get() == &counted);
        CHECK(counted.reference_count() == 1);
    }

    SECTION("should provide a method to release ownership")
    {
        CHECK(subject.release_as<test_ref_counted>() == &counted);
        CHECK(!subject);
        CHECK(counted.reference_count() == 1);
    }
}

TEST_CASE("aliasing ref ptr type deduction")
{
    int x = 3;
    test_ref_counted counted;

    auto orig = cncr::intrusive_ptr_import(&counted);
    auto synth = cncr::intrusive_ptr(orig, &x);

    CHECK(synth);
    CHECK(synth.get() == &x);
    CHECK(synth.get_handle() == orig);
}

} // namespace cncr_tests

template class dplx::cncr::intrusive_ptr<cncr_tests::test_ref_counted>;

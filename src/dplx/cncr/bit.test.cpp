
// Copyright Henrik Steffen Gaßmann 2023.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/bit.hpp"

#include <algorithm>
#include <ranges>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <dplx/predef/compiler.h>

#include <dplx/cncr/misc.hpp>
#include <dplx/cncr/workaround.h>

#include "range_generator.hpp"
#include "test_utils.hpp"

namespace cncr_tests
{

namespace
{

template <typename T>
struct endian_sample
{
    T input;
    T expected;
};

template <typename R, typename T, std::size_t N>
auto endian_samples(endian_sample<T> const (&samples)[N])
{
#if DPLX_CNCR_WORKAROUND_TESTED_AT(DPLX_COMP_CLANG, 15, 0, 0)
    typename iterator_generator<endian_sample<R>>::container_type values;
    values.reserve(N);
    for (auto &sample : samples)
    {
        values.push_back(std::bit_cast<endian_sample<R>>(sample));
    }

    return cncr_tests::from_range(std::move(values));
#else
    return cncr_tests::from_range(
            samples | std::views::transform([](endian_sample<T> const &sample) {
                return std::bit_cast<endian_sample<R>>(sample);
            }));
#endif
}

} // namespace

namespace
{

template <typename T>
constexpr endian_sample<T> byteswap_samples[3] = {};
template <typename T>
    requires(sizeof(T) == sizeof(std::uint8_t))
constexpr endian_sample<std::uint8_t> byteswap_samples<T>[] = {
        {0x1f, 0x1f},
        {0xf1, 0xf1},
        {0x13, 0x13},
};
template <typename T>
    requires(sizeof(T) == sizeof(std::uint16_t))
constexpr endian_sample<std::uint16_t> byteswap_samples<T>[] = {
        {0x1f2e, 0x2e1f},
        {0xf1e2, 0xe2f1},
        {0xac34, 0x34ac},
};
template <typename T>
    requires(sizeof(T) == sizeof(std::uint32_t))
constexpr endian_sample<std::uint32_t> byteswap_samples<T>[] = {
        {0x1f2e'3d4c, 0x4c3d'2e1f},
        {0xf1e2'd3c4, 0xc4d3'e2f1},
        {0x1234'abcd, 0xcdab'3412},
};
template <typename T>
    requires(sizeof(T) == sizeof(std::uint64_t))
constexpr endian_sample<std::uint64_t> byteswap_samples<T>[] = {
        {0x1f2e'3d4c'5b6a'7988, 0x8879'6a5b'4c3d'2e1f},
        {0xf1e2'd3c4'b5a6'9788, 0x8897'a6b5'c4d3'e2f1},
        {0x1234'5678'90ab'cdef, 0xefcd'ab90'7856'3412},
};

} // namespace

TEMPLATE_TEST_CASE("byteswap correctly reverses integral types",
                   "",
                   unsigned char,
                   signed char,
                   unsigned short,
                   short,
                   unsigned,
                   int,
                   unsigned long,
                   long,
                   unsigned long long,
                   long long,
                   char,
                   wchar_t,
                   char8_t,
                   char16_t,
                   char32_t)
{
    endian_sample<TestType> sample
            = GENERATE(endian_samples<TestType>(byteswap_samples<TestType>));
    INFO(static_cast<std::uint64_t>(sample.input));

    SECTION("projection")
    {
        CHECK(cncr::byteswap(sample.input) == sample.expected);
    }
    SECTION("inverse")
    {
        std::ranges::swap(sample.input, sample.expected);
        CHECK(cncr::byteswap(sample.input) == sample.expected);
    }
}

TEST_CASE("endian_load correctly loads a big endian value from bytes")
{
    using enum std::endian;
    auto const bytes = cncr::make_byte_array<4>({0x1f, 0x2e, 0x3d, 0x4c});
    auto const loaded = cncr::endian_load<big, std::uint32_t>(bytes.data());
    CHECK(loaded == 0x1f2e'3d4c);
}
TEST_CASE("endian_load correctly loads a little endian value from bytes")
{
    using enum std::endian;
    auto const bytes = cncr::make_byte_array<4>({0x4c, 0x3d, 0x2e, 0x1f});
    auto const loaded = cncr::endian_load<little, std::uint32_t>(bytes.data());
    CHECK(loaded == 0x1f2e'3d4c);
}
TEST_CASE("endian_load correctly loads a big endian value from uint8s")
{
    using enum std::endian;
    std::array<std::uint8_t, 4> const bytes{0x1f, 0x2e, 0x3d, 0x4c};
    auto const loaded = cncr::endian_load<big, std::uint32_t>(bytes.data());
    CHECK(loaded == 0x1f2e'3d4c);
}
TEST_CASE("endian_load correctly loads a little endian value from uint8s")
{
    using enum std::endian;
    std::array<std::uint8_t, 4> const bytes{0x4c, 0x3d, 0x2e, 0x1f};
    auto const loaded = cncr::endian_load<little, std::uint32_t>(bytes.data());
    CHECK(loaded == 0x1f2e'3d4c);
}

TEST_CASE("endian_store correctly stores a big endian value to bytes")
{
    using enum std::endian;
    constexpr unsigned value = 0x1f2e'3d4c;
    auto const expected = cncr::make_byte_array<4>({0x1f, 0x2e, 0x3d, 0x4c});

    std::array<std::byte, 4> stored{};
    cncr::endian_store<std::endian::big>(stored.data(), value);
    CHECK(std::ranges::equal(stored, expected));
}
TEST_CASE("endian_store correctly stores a little endian value to bytes")
{
    using enum std::endian;
    constexpr unsigned value = 0x1f2e'3d4c;
    auto const expected = cncr::make_byte_array<4>({0x4c, 0x3d, 0x2e, 0x1f});

    std::array<std::byte, 4> stored{};
    cncr::endian_store<std::endian::little>(stored.data(), value);
    CHECK(std::ranges::equal(stored, expected));
}
TEST_CASE("endian_store correctly stores a big endian value to uint8s")
{
    using enum std::endian;
    constexpr unsigned value = 0x1f2e'3d4c;
    std::array<std::uint8_t, 4> const expected{0x1f, 0x2e, 0x3d, 0x4c};

    std::array<std::uint8_t, 4> stored{};
    cncr::endian_store<std::endian::big>(stored.data(), value);
    CHECK(std::ranges::equal(stored, expected));
}
TEST_CASE("endian_store correctly stores a little endian value to uint8s")
{
    using enum std::endian;
    constexpr unsigned value = 0x1f2e'3d4c;
    std::array<std::uint8_t, 4> const expected{0x4c, 0x3d, 0x2e, 0x1f};

    std::array<std::uint8_t, 4> stored{};
    cncr::endian_store<std::endian::little>(stored.data(), value);
    CHECK(std::ranges::equal(stored, expected));
}

} // namespace cncr_tests

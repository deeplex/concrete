
// Copyright Henrik Steffen Gaßmann 2023.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#include "dplx/cncr/uuid.hpp"
//
#include "dplx/cncr/uuid.fmt.hpp"
#include "dplx/cncr/uuid.rng.hpp"
//

#include <sstream>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include <dplx/cncr/misc.hpp>

#include "test_utils.hpp"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

namespace cncr_tests
{

#if __has_include(<fmt/base.h>)
static_assert(std::is_constructible_v<fmt::formatter<cncr::uuid, char>>);
#endif

namespace
{

using test_state = cncr::blob<std::uint8_t, cncr::uuid::state_size>;

} // namespace

using namespace cncr::uuid_literals;

TEST_CASE("value initialized uuid is nil")
{
    cncr::uuid subject{};
    CHECK(subject.is_nil());
}
TEST_CASE("detects max uuid")
{
    cncr::uuid subject = "ffffffff-ffff-ffff-ffff-ffffffffffff"_uuid;
    CHECK(subject.is_max());
}

TEST_CASE("_uuid literal operator can consteval a uuid")
{
    constexpr auto subject = "47183823-2574-4bfd-b411-99ed177d3e43"_uuid;
    auto const expected
            = test_state{0xfd, 0x4b, 0x74, 0x25, 0x23, 0x38, 0x18, 0x47,
                         0x43, 0x3e, 0x7d, 0x17, 0xed, 0x99, 0x11, 0xb4};

    CHECK(subject == std::bit_cast<cncr::uuid>(expected));
}
TEST_CASE("the uuid char array constructor can consteval a uuid")
{
    constexpr auto subject = cncr::uuid("47183823-2574-4bfd-b411-99ed177d3e43");
    auto const expected
            = test_state{0xfd, 0x4b, 0x74, 0x25, 0x23, 0x38, 0x18, 0x47,
                         0x43, 0x3e, 0x7d, 0x17, 0xed, 0x99, 0x11, 0xb4};

    CHECK(subject == std::bit_cast<cncr::uuid>(expected));
}
TEST_CASE("the uuid char array constructor can consteval a uuid with alternate "
          "form")
{
    constexpr auto subject
            = cncr::uuid("{47183823-2574-4bfd-b411-99ed177d3e43}");
    auto const expected
            = test_state{0xfd, 0x4b, 0x74, 0x25, 0x23, 0x38, 0x18, 0x47,
                         0x43, 0x3e, 0x7d, 0x17, 0xed, 0x99, 0x11, 0xb4};

    CHECK(subject == std::bit_cast<cncr::uuid>(expected));
}

TEST_CASE("a uuid can be constexpr imported from canonical bytes")
{
    using namespace std::string_view_literals;
    constexpr auto canonical = cncr::make_byte_array<16>(
            {0x47, 0x18, 0x38, 0x23, 0x25, 0x74, 0x4b, 0xfd, 0xb4, 0x11, 0x99,
             0xed, 0x17, 0x7d, 0x3e, 0x43});
    constexpr cncr::uuid imported{canonical};
    CHECK(fmt::format("{}", imported)
          == "47183823-2574-4bfd-b411-99ed177d3e43"sv);
}
TEST_CASE("a uuid can be constexpr imported from canonical uint8s")
{
    using namespace std::string_view_literals;
    constexpr std::array<std::uint8_t, 16> canonical{
            0x47, 0x18, 0x38, 0x23, 0x25, 0x74, 0x4b, 0xfd,
            0xb4, 0x11, 0x99, 0xed, 0x17, 0x7d, 0x3e, 0x43};
    constexpr cncr::uuid imported{canonical};
    CHECK(fmt::format("{}", imported)
          == "47183823-2574-4bfd-b411-99ed177d3e43"sv);
}

TEST_CASE("a uuid is correctly stringified")
{
    using namespace std::string_view_literals;
    auto const subject = "47183823-2574-4bfd-b411-99ed177d3e43"_uuid;
    auto const expected = "47183823-2574-4bfd-b411-99ed177d3e43"sv;

    SECTION("via iostream operator")
    {
        std::stringstream stream;
        stream << subject;
        CHECK(stream.str() == expected);
    }
#if __cpp_lib_format >= 202'106L
    SECTION("via std::format")
    {
        auto const stringified = std::format("{}", subject);
        CHECK(stringified == expected);
    }
    SECTION("via std::format alternate form")
    {
        auto const stringified = std::format("{:#}", subject);
        CHECK(stringified == "{47183823-2574-4bfd-b411-99ed177d3e43}"sv);
    }
    SECTION("via std::format alternate form")
    {
        auto const stringified = std::format("{:#X}", subject);
        CHECK(stringified == "{47183823-2574-4BFD-B411-99ED177D3E43}"sv);
    }
#endif
#if __has_include(<fmt/base.h>)
    SECTION("via fmt::format")
    {
        auto const stringified = fmt::format("{}", subject);
        CHECK(stringified == expected);
    }
    SECTION("via fmt::format alternate form")
    {
        auto const stringified = fmt::format("{:#}", subject);
        CHECK(stringified == "{47183823-2574-4bfd-b411-99ed177d3e43}"sv);
    }
    SECTION("via std::format alternate form")
    {
        auto const stringified = fmt::format("{:#X}", subject);
        CHECK(stringified == "{47183823-2574-4BFD-B411-99ED177D3E43}"sv);
    }
#endif
}

TEST_CASE("uuids are correctly ordered")
{
    cncr::uuid orderSamples[] = {
            "00000000-0000-0000-0000-000000000000"_uuid,
            "00000000-0000-1000-8000-000000000000"_uuid,
            "00000000-0000-4000-8000-000000000000"_uuid,
            "00000000-0000-4000-8000-000000000001"_uuid,
            "00000000-0000-4000-b000-000000000000"_uuid,
            "00000000-0000-4000-bfff-ffffffffffff"_uuid,
            "00000000-0000-4001-8000-000000000001"_uuid,
            "00000000-0000-4001-b000-000000000000"_uuid,
            "00000000-0000-7000-8000-000000000000"_uuid,
            "10000000-0000-4000-8000-000000000001"_uuid,
            "ffffffff-ffff-ffff-ffff-ffffffffffff"_uuid,
    };
    for (auto it = std::begin(orderSamples), end = std::end(orderSamples);
         std::next(it) < end; ++it)
    {
        CHECK(*it != *std::next(it));
        CHECK(*it < *std::next(it));
    }
}

TEST_CASE("random_uuidv4_generator generates rfc v4 uuids")
{
    struct mocked_engine
    {
        static constexpr auto min() -> std::uint64_t
        {
            return 0U;
        }
        static constexpr auto max() -> std::uint64_t
        {
            return UINT64_MAX;
        }
        auto operator()() noexcept -> std::uint64_t
        {
            return 0U;
        }
    };
    cncr::random_uuidv4_generator subject(mocked_engine{});
    auto generated = subject();
    CHECK(generated.variant() == cncr::uuid_variant::rfc);
    CHECK(generated.version() == cncr::uuid_version::random_number_based);
    CHECK(generated == "00000000-0000-4000-8000-000000000000"_uuid);
}

// static_assert("47183823-2574-4bfd-b411-99ed177d3e43"_uuid
//               == std::bit_cast<cncr::uuid>(test_state{0x47183823, 0x25744bfd,
//                                                     0xb41199ed,
//                                                     0x177d3e43}));

} // namespace cncr_tests

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)


// Copyright Henrik Steffen Gaßmann 2023.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <bit>
#include <climits>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iosfwd>
#include <span>
#include <string_view> // currently for std::hash

#include <dplx/predef/compiler.h>

#include <dplx/cncr/bit.hpp>
#include <dplx/cncr/workaround.h>

namespace dplx::cncr
{

class uuid;

inline namespace uuid_literals
{

consteval auto operator""_uuid(char const *chars, std::size_t len) -> uuid;

}

} // namespace dplx::cncr

namespace dplx::cncr::detail
{

inline constexpr std::size_t uuid_state_size = 16;
inline constexpr std::size_t formatted_uuid_size = 36;

template <typename CharT>
inline constexpr CharT uuid_encoding_lut[39] = {};

template <typename CharT>
concept has_uuid_encoding_lut = (uuid_encoding_lut<CharT>[0] != CharT{});

template <typename CharT, typename OutIt>
constexpr auto format_uuid_to(uuid value,
                              OutIt out,
                              unsigned up = 0U,
                              bool alternateForm = false) -> OutIt;

} // namespace dplx::cncr::detail

namespace dplx::cncr
{

enum class uuid_variant
{
    ncs,
    rfc,
    microsoft,
    future,
};

enum class uuid_version
{
    unknown = -1,
    none = 0,
    time_based_gregorian = 1,
    dce_security = 2,
    name_based_md5 = 3,
    random_number_based = 4,
    name_based_sha1 = 5,
    time_based_gregorian_ordered = 6,
    time_based_unix = 7,
    vendor_specific = 8,
};

class uuid
{
    friend struct std::hash<uuid>;
    template <typename CharT, typename OutIt>
    friend constexpr auto detail::format_uuid_to(uuid value,
                                                 OutIt out,
                                                 unsigned up,
                                                 bool alternateForm) -> OutIt;
    friend consteval auto uuid_literals::operator""_uuid(char const *chars,
                                                         std::size_t len)
            -> uuid;

public:
    static constexpr std::size_t state_size = detail::uuid_state_size;

private:
    alignas(state_size)
            std::uint64_t mState[state_size / sizeof(std::uint64_t)];

    // due to a clang bug this function needs to be declared and defined before
    // its usage within the uuid constructor
    template <typename T>
    static constexpr auto import_canonical(T const *bytes) noexcept -> uuid
    {
        // initializing assembled is the whole point of this function
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
        blob<std::uint8_t, state_size, state_size> assembled;
#if defined(DPLX_COMP_CLANG_AVAILABLE)
        // these compilers have constexpr intrinsics for memcpy
        if constexpr (std::is_same_v<T, std::uint8_t>)
        {
            __builtin_memcpy(static_cast<std::uint8_t *>(assembled.values),
                             bytes, state_size);
        }
        else
        {
#endif
            DPLX_CNCR_IF_NOT_CONSTEVAL
            {
                std::memcpy(&assembled, bytes, state_size);
            }
            else [[unlikely]]
            {
                for (auto &v : assembled.values)
                {
                    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                    v = static_cast<std::uint8_t>(*bytes++);
                }
            }
#if defined(DPLX_COMP_CLANG_AVAILABLE)
        }
#endif
        return import_canonical(assembled);
    }

public:
    constexpr uuid() noexcept = default;

    constexpr explicit uuid(
            std::span<std::byte const, state_size> bytes) noexcept
        : uuid(import_canonical(bytes.data()))
    {
    }
    constexpr explicit uuid(
            std::span<std::uint8_t const, state_size> bytes) noexcept
        : uuid(import_canonical(bytes.data()))
    {
    }

    consteval explicit uuid(char const (&str)[detail::formatted_uuid_size + 1])
        : uuid(import_string(static_cast<char const *>(str),
                             detail::formatted_uuid_size))
    {
    }
    consteval explicit uuid(char const (&str)[detail::formatted_uuid_size + 3])
        : uuid(import_string(static_cast<char const *>(str),
                             detail::formatted_uuid_size + 2))
    {
    }

private:
    constexpr explicit uuid(std::uint64_t s0, std::uint64_t s1) noexcept
        : mState{s0, s1}
    {
    }

public:
    // clang-tidy flags compiler generated functions…
    // NOLINTBEGIN(cppcoreguidelines-*)
    // NOLINTBEGIN(modernize-*)
    [[nodiscard]] friend constexpr auto operator==(uuid, uuid) noexcept -> bool
            = default;
    [[nodiscard]] friend constexpr auto operator<=>(uuid, uuid) noexcept
            -> std::strong_ordering
            = default;
    // NOLINTEND(modernize-*)
    // NOLINTEND(cppcoreguidelines-*)

    [[nodiscard]] constexpr auto canonical() const noexcept
            -> blob<std::byte, state_size>
    {
        uuid self(*this);
        if constexpr (std::endian::native == std::endian::little)
        {
            self.mState[0] = cncr::byteswap(self.mState[0]);
            self.mState[1] = cncr::byteswap(self.mState[1]);
        }
        return std::bit_cast<blob<std::byte, state_size>>(self);
    }

    [[nodiscard]] constexpr auto is_nil() const noexcept -> bool
    {
        // we don't include <algorithm> for compiler throughput reasons
        // NOLINTNEXTLINE(readability-use-anyofallof)
        for (auto bits : mState)
        {
            if (bits != 0U)
            {
                return false;
            }
        }
        return true;
    }
    [[nodiscard]] constexpr auto is_max() const noexcept -> bool
    {
        // we don't include <algorithm> for compiler throughput reasons
        // NOLINTNEXTLINE(readability-use-anyofallof)
        for (auto bits : mState)
        {
            if (bits != UINT64_MAX)
            {
                return false;
            }
        }
        return true;
    }
    [[nodiscard]] constexpr auto variant() const noexcept -> uuid_variant
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto const variantOctet = mState[1] >> 61;
        if (variantOctet < 0b100)
        {
            return uuid_variant::ncs;
        }
        if (variantOctet < 0b110)
        {
            return uuid_variant::rfc;
        }
        return variantOctet == 0b110 ? uuid_variant::microsoft
                                     : uuid_variant::future;
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }
    [[nodiscard]] constexpr auto version() const noexcept -> uuid_version
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        auto const nibble = (mState[0] >> 12) & 0b1111U;
        constexpr unsigned maxKnownValue = 0b1000;
        return nibble <= maxKnownValue ? static_cast<uuid_version>(nibble)
                                       : uuid_version::unknown;
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    template <typename CharT, typename Traits>
        requires detail::has_uuid_encoding_lut<CharT>
    friend inline auto operator<<(std::basic_ostream<CharT, Traits> &os,
                                  uuid value)
            -> std::basic_ostream<CharT, Traits> &
    {
        CharT fmtBuffer[detail::formatted_uuid_size];
        detail::format_uuid_to<CharT, CharT *>(value,
                                               static_cast<CharT *>(fmtBuffer));
        os.rdbuf()->sputn(static_cast<CharT *>(fmtBuffer),
                          detail::formatted_uuid_size);
        return os;
    }

private:
    static constexpr auto
    import_canonical(blob<std::uint8_t, state_size, state_size> bytes) noexcept
            -> uuid
    {
        static_assert(std::endian::native == std::endian::little
                              || std::endian::native == std::endian::big,
                      "unsupported endianness");

#if defined(DPLX_COMP_CLANG_AVAILABLE) || defined(DPLX_COMP_GNUC_AVAILABLE)    \
        || defined(DPLX_COMP_MSVC_AVAILABLE)
        uuid value = __builtin_bit_cast(uuid, bytes);
#else
        uuid value = std::bit_cast<uuid>(bytes);
#endif

        if constexpr (std::endian::native == std::endian::little)
        {
#if defined(DPLX_COMP_CLANG_AVAILABLE) || defined(DPLX_COMP_GNUC_AVAILABLE)
            // these compilers have constexpr intrinsics for byteswap
            value.mState[0] = __builtin_bswap64(value.mState[0]);
            value.mState[1] = __builtin_bswap64(value.mState[1]);
#elif defined(DPLX_CNCR_BYTESWAP64_INTRINSIC)
            DPLX_CNCR_IF_NOT_CONSTEVAL [[likely]]
            {
                value.mState[0]
                        = DPLX_CNCR_BYTESWAP64_INTRINSIC(value.mState[0]);
                value.mState[1]
                        = DPLX_CNCR_BYTESWAP64_INTRINSIC(value.mState[1]);
                return value;
            }
            value.mState[0] = cncr::byteswap(value.mState[0]);
            value.mState[1] = cncr::byteswap(value.mState[1]);
#else // no intrinsic => fallback to mask and shift / std implementation
            value.mState[0] = cncr::byteswap(value.mState[0]);
            value.mState[1] = cncr::byteswap(value.mState[1]);
#endif
        }
        return value;
    }
    static consteval auto import_string(char const *chars, std::size_t len)
            -> uuid
    {
        // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        if (len != detail::formatted_uuid_size
            && len != detail::formatted_uuid_size + 2)
        {
            throw "_uuid couldn't parse string literal due to illegal length";
        }
        if (len == detail::formatted_uuid_size + 2)
        {
            if (chars[0] != '{'
                || chars[detail::formatted_uuid_size + 1] != '}')
            {
                throw "_uuid couldn't parse the alternate form due to illegal "
                      "braces";
            }
            ++chars;
        }
        return uuid((eval_hex_digit(chars[0]) << 60)
                            | (eval_hex_digit(chars[1]) << 56)
                            | (eval_hex_digit(chars[2]) << 52)
                            | (eval_hex_digit(chars[3]) << 48)
                            | (eval_hex_digit(chars[4]) << 44)
                            | (eval_hex_digit(chars[5]) << 40)
                            | (eval_hex_digit(chars[6]) << 36)
                            | (eval_hex_digit(chars[7]) << 32)
                            | (eval_hex_digit(chars[9]) << 28)
                            | (eval_hex_digit(chars[10]) << 24)
                            | (eval_hex_digit(chars[11]) << 20)
                            | (eval_hex_digit(chars[12]) << 16)
                            | (eval_hex_digit(chars[14]) << 12)
                            | (eval_hex_digit(chars[15]) << 8)
                            | (eval_hex_digit(chars[16]) << 4)
                            | (eval_hex_digit(chars[17]) << 0),
                    (eval_hex_digit(chars[19]) << 60)
                            | (eval_hex_digit(chars[20]) << 56)
                            | (eval_hex_digit(chars[21]) << 52)
                            | (eval_hex_digit(chars[22]) << 48)
                            | (eval_hex_digit(chars[24]) << 44)
                            | (eval_hex_digit(chars[25]) << 40)
                            | (eval_hex_digit(chars[26]) << 36)
                            | (eval_hex_digit(chars[27]) << 32)
                            | (eval_hex_digit(chars[28]) << 28)
                            | (eval_hex_digit(chars[29]) << 24)
                            | (eval_hex_digit(chars[30]) << 20)
                            | (eval_hex_digit(chars[31]) << 16)
                            | (eval_hex_digit(chars[32]) << 12)
                            | (eval_hex_digit(chars[33]) << 8)
                            | (eval_hex_digit(chars[34]) << 4)
                            | (eval_hex_digit(chars[35]) << 0));
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
    static consteval auto eval_hex_digit(char digit) -> std::uint64_t
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        unsigned const udigit = static_cast<unsigned char>(digit);
        unsigned const maybeDecimal = udigit - '0';
        unsigned const maybeAlpha = (udigit | 0x20U) - 'a';
        return maybeDecimal <= 9U ? maybeDecimal
               : maybeAlpha <= 5U ? 0xa + maybeAlpha
                                  : throw "illegal hex digit";
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }
};

} // namespace dplx::cncr

template <>
struct std::hash<dplx::cncr::uuid>
{
    using is_avalanching = void;

    // derivative of xxHASH64
    // https://github.com/Cyan4973/xxHash/blob/2b328a10983d232364ceda15df1d33531b5f0eb5/doc/xxhash_spec.md
    constexpr auto operator()(dplx::cncr::uuid value) const -> std::size_t
    {
        // initialize
        std::uint64_t acc = PRIME64_5;
        // add input length
        acc += 2 * sizeof(std::uint64_t);

        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

        // "remaining" input
        acc ^= xxHash64_round(0U, value.mState[0]);
        acc = (acc << 27) * PRIME64_1;
        acc += PRIME64_4;
        acc ^= xxHash64_round(0U, value.mState[1]);
        acc = (acc << 27) * PRIME64_1;
        acc += PRIME64_4;

        // mix
        acc ^= acc >> 33;
        acc *= PRIME64_2;
        acc ^= acc >> 29;
        acc *= PRIME64_3;
        acc ^= acc >> 32;

        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
        return acc;
    }

private:
    static constexpr std::uint64_t PRIME64_1 = 0x9e37'79b1'85eb'ca87U;
    static constexpr std::uint64_t PRIME64_2 = 0xc2b2'ae3d'27d4'eb4fU;
    static constexpr std::uint64_t PRIME64_3 = 0x1656'67b1'9e37'79f9U;
    static constexpr std::uint64_t PRIME64_4 = 0x85eb'ca77'c2b2'ae63U;
    static constexpr std::uint64_t PRIME64_5 = 0x27d4'eb2f'1656'67c5U;

    static constexpr auto xxHash64_round(std::uint64_t accN,
                                         std::uint64_t const laneN) noexcept
            -> std::uint64_t
    {
        accN += laneN * PRIME64_2;
        accN <<= 31; // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        return accN * PRIME64_1;
    }
};

namespace dplx::cncr::detail
{

template <>
inline constexpr char uuid_encoding_lut<char>[39]
        = "0123456789abcdef0123456789ABCDEF{-}#xX";
template <>
inline constexpr wchar_t uuid_encoding_lut<wchar_t>[39]
        = L"0123456789abcdef0123456789ABCDEF{-}#xX";
template <>
inline constexpr char8_t uuid_encoding_lut<char8_t>[39]
        = u8"0123456789abcdef0123456789ABCDEF{-}#xX";
template <>
inline constexpr char16_t uuid_encoding_lut<char16_t>[39]
        = u"0123456789abcdef0123456789ABCDEF{-}#xX";
template <>
inline constexpr char32_t uuid_encoding_lut<char32_t>[39]
        = U"0123456789abcdef0123456789ABCDEF{-}#xX";

template <typename CharT, typename OutIt>
constexpr auto
format_uuid_to(uuid value, OutIt out, unsigned up, bool alternateForm) -> OutIt
{
    constexpr auto openingBraceIdx = 32;
    constexpr auto closingBraceIdx = 34;
    constexpr auto hyphenIdx = 33;

    if constexpr (std::endian::native == std::endian::little)
    {
        value.mState[0] = cncr::byteswap(value.mState[0]);
        value.mState[1] = cncr::byteswap(value.mState[1]);
    }
    auto const state
            = std::bit_cast<blob<std::uint8_t, uuid_state_size>>(value);

    if (alternateForm)
    {
        *out++ = uuid_encoding_lut<CharT>[openingBraceIdx];
    }
    for (std::size_t i = 0; i < sizeof(state); ++i)
    {
        constexpr unsigned low_4bit_mask = 0xfU;
        // NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
        *out++ = uuid_encoding_lut<
                CharT>[((state.values[i] >> 4) & low_4bit_mask) | up];
        *out++ = uuid_encoding_lut<
                CharT>[((state.values[i] >> 0) & low_4bit_mask) | up];
        // NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)

        // insert hyphens in the appropriate places
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
        if (i == 3 || i == 5 || i == 7 || i == 9)
        {
            *out++ = uuid_encoding_lut<CharT>[hyphenIdx];
        }
    }
    if (alternateForm)
    {
        *out++ = uuid_encoding_lut<CharT>[closingBraceIdx];
    }
    return out;
}

} // namespace dplx::cncr::detail

namespace dplx::cncr::inline uuid_literals
{

consteval auto operator""_uuid(char const *chars, std::size_t len) -> uuid
{
    return uuid::import_string(chars, len);
}

// clang-format off
} // namespace dplx::cncr::inline uuid_literals
// clang-format on

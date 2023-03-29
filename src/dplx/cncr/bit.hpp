
// Copyright Henrik Steffen Gaßmann 2023.
// Copyright Peter Dimov 2019, 2020.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <bit>
#include <cstddef>
#include <limits>
#include <type_traits>

#include <dplx/predef/compiler.h>

#include <dplx/cncr/config.hpp>
#include <dplx/cncr/utils.hpp>

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

// compiler auto detection is mutually exclusiv with user supplied intrinsics
// which allows the user to opt out of or into specific intrinsics
#if !defined(DPLX_CNCR_BYTESWAP16_INTRINSIC)                                   \
        && !defined(DPLX_CNCR_BYTESWAP32_INTRINSIC)                            \
        && !defined(DPLX_CNCR_BYTESWAP64_INTRINSIC)

#if defined(DPLX_COMP_MSVC_AVAILABLE)
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/byteswap-uint64-byteswap-ulong-byteswap-ushort
#include <cstdlib>
#define DPLX_CNCR_BYTESWAP16_INTRINSIC(value)                                  \
    _byteswap_ushort(static_cast<unsigned short>(value))
#define DPLX_CNCR_BYTESWAP32_INTRINSIC(value)                                  \
    _byteswap_ulong(static_cast<unsigned long>(value))
#define DPLX_CNCR_BYTESWAP64_INTRINSIC(value)                                  \
    _byteswap_uint64(static_cast<unsigned __int64>(value))

#elif defined(DPLX_COMP_CLANG_AVAILABLE) || defined(DPLX_COMP_GNUC_AVAILABLE)
// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
#include <cstdint>
#define DPLX_CNCR_BYTESWAP16_INTRINSIC(value)                                  \
    __builtin_bswap16(static_cast<uint16_t>(value))
#define DPLX_CNCR_BYTESWAP32_INTRINSIC(value)                                  \
    __builtin_bswap32(static_cast<uint32_t>(value))
#define DPLX_CNCR_BYTESWAP64_INTRINSIC(value)                                  \
    __builtin_bswap64(static_cast<uint64_t>(value))

#endif

// NOLINTEND(cppcoreguidelines-macro-usage)

#if DPLX_CNCR_USE_STD_BYTESWAP

namespace dplx::cncr
{

static_assert(__cpp_lib_byteswap >= 202110L,
              "USE_STD_BYTESWAP has been configured, but this TU isn't "
              "compiled with a sufficiently C++23 compliant compiler/mode");
using std::byteswap;

} // namespace dplx::cncr

#else

#endif

namespace dplx::cncr
{

template <typename T>
    requires std::is_integral_v<T>
constexpr auto byteswap(T value) noexcept -> T
{
    static_assert(std::has_unique_object_representations_v<T>,
                  "byteswap isn't well defined for padded types");

    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

    // -- portable approach suggested by tymofey, with avoidance of undefined
    //    behavior as suggested by Giovanni Piero Deretta, with a further
    //    refinement suggested by Pyry Jahkola.
    if constexpr (sizeof(T) == sizeof(std::byte))
    {
        return value;
    }
    else if constexpr (sizeof(T) == sizeof(std::uint16_t))
    {
#if defined(DPLX_CNCR_BYTESWAP16_INTRINSIC)
        DPLX_CNCR_IF_NOT_CONSTEVAL
        {
            return static_cast<T>(DPLX_CNCR_BYTESWAP16_INTRINSIC(value));
        }
#endif
        auto const x = static_cast<std::uint16_t>(value);
        return static_cast<T>((x << 8) | (x >> 8));
    }
    else if constexpr (sizeof(T) == sizeof(std::uint32_t))
    {
#if defined(DPLX_CNCR_BYTESWAP32_INTRINSIC)
        DPLX_CNCR_IF_NOT_CONSTEVAL
        {
            return static_cast<T>(DPLX_CNCR_BYTESWAP32_INTRINSIC(value));
        }
#endif
        // false positive; the following code is never instantiated with
        // signed char
        // NOLINTNEXTLINE(bugprone-signed-char-misuse)
        auto const x = static_cast<std::uint32_t>(value);
        auto const step16 = x << 16 | x >> 16;
        return static_cast<T>(((step16 << 8) & 0xff00ff00U)
                              | ((step16 >> 8) & 0x00ff00ffU));
    }
    else if constexpr (sizeof(T) == sizeof(std::uint64_t))
    {
#if defined(DPLX_CNCR_BYTESWAP64_INTRINSIC)
        DPLX_CNCR_IF_NOT_CONSTEVAL
        {
            return static_cast<T>(DPLX_CNCR_BYTESWAP64_INTRINSIC(value));
        }
#endif
        auto const x = static_cast<std::uint64_t>(value);
        auto const step32 = x << 32 | x >> 32;
        auto const step16 = (step32 & 0x0000ffff0000ffffU) << 16
                          | (step32 & 0xffff0000ffff0000U) >> 16;
        return static_cast<T>((step16 & 0x00ff00ff00ff00ffU) << 8
                              | (step16 & 0xff00ff00ff00ff00U) >> 8);
    }
    else
    {
        static_assert(sizeof(T) == 1, "not implemented");
    }
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
}

} // namespace dplx::cncr

#endif

namespace dplx::cncr
{

template <std::endian Order, typename T>
    requires std::is_integral_v<T>
DPLX_ATTR_FORCE_INLINE constexpr void endian_store(std::byte *dest,
                                                   T value) noexcept
{
    if (Order != std::endian::native)
    {
        value = cncr::byteswap<T>(value);
    }
    auto const raw
            = std::bit_cast<blob<std::byte, sizeof(T), alignof(T)>>(value);
    // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (auto src = static_cast<std::byte *>(raw.values),
              srcEnd = static_cast<std::byte *>(raw.values) + sizeof(T);
         src != srcEnd; ++src, ++dest)
    {
        *dest = *src;
    }
    // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
}
template <std::endian Order, typename T>
    requires std::is_integral_v<T>
DPLX_ATTR_FORCE_INLINE constexpr void endian_store(std::uint8_t *dest,
                                                   T value) noexcept
{
    if (Order != std::endian::native)
    {
        value = cncr::byteswap<T>(value);
    }
    auto const raw
            = std::bit_cast<blob<std::uint8_t, sizeof(T), alignof(T)>>(value);
    // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (auto src = static_cast<std::uint8_t *>(raw.values),
              srcEnd = static_cast<std::uint8_t *>(raw.values) + sizeof(T);
         src != srcEnd; ++src, ++dest)
    {
        *dest = *src;
    }
    // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
}
template <std::endian Order, typename T>
    requires std::is_integral_v<T>
DPLX_ATTR_FORCE_INLINE constexpr auto endian_load(std::byte const *src) noexcept
        -> T
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    alignas(T) blob<std::byte, sizeof(T), alignof(T)> raw;
    // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (auto dest = static_cast<std::byte *>(raw.values),
              destEnd = static_cast<std::byte *>(raw.values) + sizeof(T);
         dest != destEnd; ++src, ++dest)
    {
        *dest = *src;
    }
    // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

    if constexpr (Order != std::endian::native)
    {
        return cncr::byteswap<T>(std::bit_cast<T>(raw));
    }
    else
    {
        return std::bit_cast<T>(raw);
    }
}
template <std::endian Order, typename T>
    requires std::is_integral_v<T>
DPLX_ATTR_FORCE_INLINE constexpr auto
endian_load(std::uint8_t const *src) noexcept -> T
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    alignas(T) blob<std::uint8_t, sizeof(T), alignof(T)> raw;
    // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (auto dest = static_cast<std::uint8_t *>(raw.values),
              destEnd = static_cast<std::uint8_t *>(raw.values) + sizeof(T);
         dest != destEnd; ++src, ++dest)
    {
        *dest = *src;
    }
    // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

    if constexpr (Order != std::endian::native)
    {
        return cncr::byteswap<T>(std::bit_cast<T>(raw));
    }
    else
    {
        return std::bit_cast<T>(raw);
    }
}

} // namespace dplx::cncr

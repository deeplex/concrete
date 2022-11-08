
// Copyright Henrik Steffen Gaßmann 2022
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cstddef>
#include <type_traits>

#if defined(_MSC_VER) // MSVC
#define DPLX_ATTR_FORCE_INLINE __forceinline
#elif defined(__GNUC__) // GCC, Clang, ICC
#define DPLX_ATTR_FORCE_INLINE [[gnu::always_inline]] inline
#else
#define DPLX_ATTR_FORCE_INLINE inline
#endif

#if __has_cpp_attribute(msvc::no_unique_address)
#define DPLX_ATTR_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#elif __has_cpp_attribute(no_unique_address)
#define DPLX_ATTR_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define DPLX_ATTR_NO_UNIQUE_ADDRESS
#endif

namespace dplx::cncr
{

[[noreturn]] DPLX_ATTR_FORCE_INLINE void unreachable() noexcept
{
    // Uses compiler specific extensions if possible.
    // Even if no extension is used, undefined behavior is still raised by
    // an empty function body and the noreturn attribute.
#if defined(__GNUC__) // GCC, Clang, ICC
    __builtin_unreachable();
#elif defined(_MSC_VER) // MSVC
    __assume(false);
#endif
}

inline constexpr struct to_underlying_fn
{
    template <typename Enum>
    requires std::is_enum_v<Enum> //
            DPLX_ATTR_FORCE_INLINE constexpr auto
            operator()(Enum value) const noexcept
            -> std::underlying_type_t<Enum>
    {
        return static_cast<std::underlying_type_t<Enum>>(value);
    }
} to_underlying{};

inline constexpr struct is_null_byte_fn
{
    DPLX_ATTR_FORCE_INLINE constexpr auto
    operator()(std::byte const value) const noexcept -> bool
    {
        return value == std::byte{};
    }
} is_null_byte{};

inline constexpr struct is_non_null_byte_fn
{
    DPLX_ATTR_FORCE_INLINE constexpr auto
    operator()(std::byte const value) const noexcept -> bool
    {
        return value != std::byte{};
    }
} is_non_null_byte{};

} // namespace dplx::cncr

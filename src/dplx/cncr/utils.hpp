
// Copyright Henrik Steffen Gaßmann 2022
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cstddef>
#include <type_traits>

#if defined(_MSC_VER)   // MSVC
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

#if __cpp_if_consteval >= 202'106L
#define DPLX_CNCR_IF_CONSTEVAL     if consteval
#define DPLX_CNCR_IF_NOT_CONSTEVAL if not consteval
#else
#define DPLX_CNCR_IF_CONSTEVAL     if (std::is_constant_evaluated())
#define DPLX_CNCR_IF_NOT_CONSTEVAL if (not std::is_constant_evaluated())
#endif

namespace dplx::cncr
{

[[noreturn]] DPLX_ATTR_FORCE_INLINE void unreachable() noexcept
{
    // Uses compiler specific extensions if possible.
    // Even if no extension is used, undefined behavior is still raised by
    // an empty function body and the noreturn attribute.
#if defined(__GNUC__)   // GCC, Clang, ICC
    __builtin_unreachable();
#elif defined(_MSC_VER) // MSVC
    __assume(false);
#endif
}

/**
 * \brief A utility type for inspection of the underlying representation via
 * `std::bit_cast`'ing.
 */
template <typename T, std::size_t N, std::size_t Alignment = alignof(T)>
    requires std::is_trivially_copyable_v<T>
struct blob
{
    alignas(Alignment) T values[N];
};

inline constexpr struct to_underlying_fn
{
    template <typename Enum>
        requires std::is_enum_v<Enum>
    DPLX_ATTR_FORCE_INLINE constexpr auto operator()(Enum value) const noexcept
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

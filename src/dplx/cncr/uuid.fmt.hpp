
// Copyright Henrik Steffen Gaßmann 2023.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <version>

#include <dplx/cncr/uuid.hpp>

#if __cpp_lib_format >= 202'106L
#include <format>
#endif

#if __has_include(<fmt/base.h>)
#include <fmt/base.h>
#endif

namespace dplx::cncr::detail
{

enum class uuid_format_casing : unsigned char
{
    lower = 0x00,
    upper = 0x10,
};

template <typename CharT, template <typename> typename ParseContext>
    requires has_uuid_encoding_lut<CharT>
struct basic_uuid_formatter
{
private:
    uuid_format_casing mCasing{uuid_format_casing::lower};
    bool mAlternateForm{false};

public:
    constexpr auto parse(ParseContext<CharT> &ctx) noexcept ->
            typename ParseContext<CharT>::iterator
    {
        constexpr auto formatSpecEnd = uuid_encoding_lut<CharT>[34];
        constexpr auto alternateForm = uuid_encoding_lut<CharT>[35];
        constexpr auto lowerHex = uuid_encoding_lut<CharT>[36];
        constexpr auto upperHex = uuid_encoding_lut<CharT>[37];

        *this = {}; // reset this to default options

        auto it = ctx.begin();
        auto const end = ctx.end();
        if (it == end || *it == formatSpecEnd)
        {
            return it;
        }

        if (*it == alternateForm)
        {
            mAlternateForm = true;
            ++it;
            if (it == end)
            {
                return it;
            }
        }

        if (*it == upperHex)
        {
            mCasing = uuid_format_casing::upper;
            ++it;
        }
        else if (*it == lowerHex)
        {
            ++it;
        }
        return it;
    }
    template <typename FormatContext>
    constexpr auto format(dplx::cncr::uuid value, FormatContext &ctx) const ->
            typename FormatContext::iterator
    {
        return detail::format_uuid_to<CharT, typename FormatContext::iterator>(
                value, ctx.out(), static_cast<unsigned>(mCasing),
                mAlternateForm);
    }
};

} // namespace dplx::cncr::detail

#if __cpp_lib_format >= 202'106L
template <typename CharT>
struct std::formatter<dplx::cncr::uuid, CharT>
    : dplx::cncr::detail::basic_uuid_formatter<CharT,
                                               std::basic_format_parse_context>
{
};
#endif

#if __has_include(<fmt/base.h>)
namespace dplx::cncr::detail
{

template <typename CharT>
using fmt_basic_format_parse_context = fmt::basic_format_parse_context<CharT>;

}

template <typename CharT>
struct fmt::formatter<dplx::cncr::uuid, CharT, void>
    : dplx::cncr::detail::basic_uuid_formatter<
              CharT,
              dplx::cncr::detail::fmt_basic_format_parse_context>
{
};
template <>
struct fmt::formatter<dplx::cncr::uuid, char, void>
    : dplx::cncr::detail::basic_uuid_formatter<
              char,
              dplx::cncr::detail::fmt_basic_format_parse_context>
{
};
#endif

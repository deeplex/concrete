
// Copyright Henrik Steffen Gaßmann 2018
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

#pragma once

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

#if __has_include(<SDKDDKVer.h>) && (_WIN32 || _WIN32_WINNT)
// _WIN32_WINNT is defined per compiler flag
#include <SDKDDKVer.h>

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN 1
#define DPLX_CNCR_VC_EXTRALEAN
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#define DPLX_CNCR_WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX 1
#define DPLX_CNCR_NOMINMAX
#endif

#include <Windows.h>

#ifdef DPLX_CNCR_NOMINMAX
#undef DPLX_CNCR_NOMINMAX
#undef NOMINMAX
#endif

#ifdef DPLX_CNCR_WIN32_LEAN_AND_MEAN
#undef DPLX_CNCR_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#endif
#ifdef DPLX_CNCR_VC_EXTRALEAN
#undef DPLX_CNCR_VC_EXTRALEAN
#undef VC_EXTRALEAN
#endif

#endif

// NOLINTEND(cppcoreguidelines-macro-usage)

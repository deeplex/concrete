
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

#define VC_EXTRALEAN 1
#define WIN32_LEAN_AND_MEAN 1

#define NOMINMAX 1

#include <windows.h>

#endif

// NOLINTEND(cppcoreguidelines-macro-usage)

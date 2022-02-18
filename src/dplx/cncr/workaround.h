
// Copyright Henrik Steffen Gaßmann 2022.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include <dplx/predef/workaround.h>

#define DPLX_CNCR_WORKAROUND(symbol, comp, major, minor, patch)                \
    DPLX_XDEF_WORKAROUND(DPLX_CNCR_DISABLE_WORKAROUNDS, symbol, comp, major,    \
                        minor, patch)

#define DPLX_CNCR_WORKAROUND_TESTED_AT(symbol, major, minor, patch)            \
    DPLX_XDEF_WORKAROUND_TESTED_AT(DPLX_CNCR_DISABLE_WORKAROUNDS,               \
                                  DPLX_CNCR_FLAG_OUTDATED_WORKAROUNDS, symbol, \
                                  major, minor, patch)

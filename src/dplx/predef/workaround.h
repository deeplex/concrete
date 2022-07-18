
// Copyright Rene Rivera 2017.
// Copyright Henrik Steffen Gaßmann 2021-2022.
//
// Distributed under the Boost Software License, Version 1.0.
//         (See accompanying file LICENSE or copy at
//           https://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include <dplx/predef/version_number.h>

// these macros are very similar to those in <boost/predef/other/workaround.h>
// but offer library specific configuration knobs

// guard for bugs which have been resolved by a known (compiler) version
#define DPLX_XDEF_WORKAROUND(disable, symbol, comp, major, minor, patch)       \
    (!(disable)) && ((symbol) >= DPLX_VERSION_NUMBER_AVAILABLE)                \
            && ((symbol)comp(DPLX_VERSION_NUMBER((major), (minor), (patch))))

// guard for bugs which have _not_ been resolved by a known (compiler) version
// i.e. we need to periodically test whether they have been resolved
// after which we can move them in the upper category
#define DPLX_XDEF_WORKAROUND_TESTED_AT(disable, flagOutdated, symbol, major,   \
                                       minor, patch)                           \
    !(disable) && ((symbol) >= DPLX_VERSION_NUMBER_AVAILABLE)                  \
            && (!(flagOutdated)                                                \
                || ((symbol) <= DPLX_VERSION_NUMBER((major), (minor), (patch)) \
                            ? 1                                                \
                            : (1 % 0)))

/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_RS6K_H
#define DPLX_PREDEF_ARCHITECTURE_RS6K_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_RS6000`

http://en.wikipedia.org/wiki/RS/6000[RS/6000] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__THW_RS6000+` | {predef_detection}
| `+_IBMR2+` | {predef_detection}
| `+_POWER+` | {predef_detection}
| `+_ARCH_PWR+` | {predef_detection}
| `+_ARCH_PWR2+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_ARCH_RS6000 DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__THW_RS6000) || defined(_IBMR2) || \
    defined(_POWER) || defined(_ARCH_PWR) || \
    defined(_ARCH_PWR2)
#   undef DPLX_ARCH_RS6000
#   define DPLX_ARCH_RS6000 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_ARCH_RS6000
#   define DPLX_ARCH_RS6000_AVAILABLE
#endif

#if DPLX_ARCH_RS6000
#   undef DPLX_ARCH_WORD_BITS_32
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_RS6000_NAME "RS/6000"

#define DPLX_ARCH_PWR DPLX_ARCH_RS6000

#if DPLX_ARCH_PWR
#   define DPLX_ARCH_PWR_AVAILABLE
#endif

#if DPLX_ARCH_PWR
#   undef DPLX_ARCH_WORD_BITS_32
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_PWR_NAME DPLX_ARCH_RS6000_NAME

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_RS6000,DPLX_ARCH_RS6000_NAME)

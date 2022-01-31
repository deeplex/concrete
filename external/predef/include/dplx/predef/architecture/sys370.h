/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_SYS370_H
#define DPLX_PREDEF_ARCHITECTURE_SYS370_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_SYS370`

http://en.wikipedia.org/wiki/System/370[System/370] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__370__+` | {predef_detection}
| `+__THW_370__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_ARCH_SYS370 DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__370__) || defined(__THW_370__)
#   undef DPLX_ARCH_SYS370
#   define DPLX_ARCH_SYS370 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_ARCH_SYS370
#   define DPLX_ARCH_SYS370_AVAILABLE
#endif

#if DPLX_ARCH_SYS370
#   undef DPLX_ARCH_WORD_BITS_32
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_SYS370_NAME "System/370"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_SYS370,DPLX_ARCH_SYS370_NAME)

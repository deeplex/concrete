/*
Copyright Rene Rivera 2013-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_BLACKFIN_H
#define DPLX_PREDEF_ARCHITECTURE_BLACKFIN_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_BLACKFIN`

Blackfin Processors from Analog Devices.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__bfin__+` | {predef_detection}
| `+__BFIN__+` | {predef_detection}
| `bfin` | {predef_detection}
| `BFIN` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_ARCH_BLACKFIN DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__bfin__) || defined(__BFIN__) || \
    defined(bfin) || defined(BFIN)
#   undef DPLX_ARCH_BLACKFIN
#   define DPLX_ARCH_BLACKFIN DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_ARCH_BLACKFIN
#   define DPLX_ARCH_BLACKFIN_AVAILABLE
#endif

#if DPLX_ARCH_BLACKFIN
#   undef DPLX_ARCH_WORD_BITS_16
#   define DPLX_ARCH_WORD_BITS_16 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_BLACKFIN_NAME "Blackfin"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_BLACKFIN,DPLX_ARCH_BLACKFIN_NAME)

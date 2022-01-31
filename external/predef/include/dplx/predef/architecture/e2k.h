/*
Copyright Konstantin Ivlev 2021
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_E2K_H
#define DPLX_PREDEF_ARCHITECTURE_E2K_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_E2K`

https://en.wikipedia.org/wiki/Elbrus_2000[E2K] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__e2k__+` | {predef_detection}

| `+__e2k__+` | V.0.0
|===
*/ // end::reference[]

#define DPLX_ARCH_E2K DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__e2k__)
#   undef DPLX_ARCH_E2K
#   if !defined(DPLX_ARCH_E2K) && defined(__iset__)
#       define DPLX_ARCH_E2K DPLX_VERSION_NUMBER(__iset__,0,0)
#   endif
#   if !defined(DPLX_ARCH_E2K)
#       define DPLX_ARCH_E2K DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_ARCH_E2K
#   define DPLX_ARCH_E2K_AVAILABLE
#endif

#if DPLX_ARCH_E2K
#   define DPLX_ARCH_WORD_BITS_64 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_E2K_NAME "E2K"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_E2K,DPLX_ARCH_E2K_NAME)

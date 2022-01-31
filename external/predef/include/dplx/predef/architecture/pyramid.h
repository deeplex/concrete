/*
Copyright Rene Rivera 2011-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_PYRAMID_H
#define DPLX_PREDEF_ARCHITECTURE_PYRAMID_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_PYRAMID`

Pyramid 9810 architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `pyr` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_ARCH_PYRAMID DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(pyr)
#   undef DPLX_ARCH_PYRAMID
#   define DPLX_ARCH_PYRAMID DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_ARCH_PYRAMID
#   define DPLX_ARCH_PYRAMID_AVAILABLE
#endif

#if DPLX_ARCH_PYRAMID
#   undef DPLX_ARCH_WORD_BITS_32
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_PYRAMID_NAME "Pyramid 9810"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_PYRAMID,DPLX_ARCH_PYRAMID_NAME)

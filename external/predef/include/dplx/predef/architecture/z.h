/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_Z_H
#define DPLX_PREDEF_ARCHITECTURE_Z_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_Z`

http://en.wikipedia.org/wiki/Z/Architecture[z/Architecture] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__SYSC_ZARCH__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_ARCH_Z DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__SYSC_ZARCH__)
#   undef DPLX_ARCH_Z
#   define DPLX_ARCH_Z DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_ARCH_Z
#   define DPLX_ARCH_Z_AVAILABLE
#endif

#if DPLX_ARCH_Z
#   undef DPLX_ARCH_WORD_BITS_64
#   define DPLX_ARCH_WORD_BITS_64 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_Z_NAME "z/Architecture"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_Z,DPLX_ARCH_Z_NAME)

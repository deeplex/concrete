/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_ARCHITECTURE_SYS390_H
#define DPLX_PREDEF_ARCHITECTURE_SYS390_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_ARCH_SYS390`

http://en.wikipedia.org/wiki/System/390[System/390] architecture.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__s390__+` | {predef_detection}
| `+__s390x__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_ARCH_SYS390 DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__s390__) || defined(__s390x__)
#   undef DPLX_ARCH_SYS390
#   define DPLX_ARCH_SYS390 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_ARCH_SYS390
#   define DPLX_ARCH_SYS390_AVAILABLE
#endif

#if DPLX_ARCH_SYS390
#   undef DPLX_ARCH_WORD_BITS_32
#   define DPLX_ARCH_WORD_BITS_32 DPLX_VERSION_NUMBER_AVAILABLE
#endif

#define DPLX_ARCH_SYS390_NAME "System/390"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_ARCH_SYS390,DPLX_ARCH_SYS390_NAME)

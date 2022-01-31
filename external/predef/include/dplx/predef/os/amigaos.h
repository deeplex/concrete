/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_AMIGAOS_H
#define DPLX_PREDEF_OS_AMIGAOS_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_AMIGAOS`

http://en.wikipedia.org/wiki/AmigaOS[AmigaOS] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `AMIGA` | {predef_detection}
| `+__amigaos__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_OS_AMIGAOS DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(AMIGA) || defined(__amigaos__) \
    )
#   undef DPLX_OS_AMIGAOS
#   define DPLX_OS_AMIGAOS DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_OS_AMIGAOS
#   define DPLX_OS_AMIGAOS_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_AMIGAOS_NAME "AmigaOS"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_AMIGAOS,DPLX_OS_AMIGAOS_NAME)

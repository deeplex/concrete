/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_HPUX_H
#define DPLX_PREDEF_OS_HPUX_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_HPUX`

http://en.wikipedia.org/wiki/HP-UX[HP-UX] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `hpux` | {predef_detection}
| `+_hpux+` | {predef_detection}
| `+__hpux+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_OS_HPUX DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(hpux) || defined(_hpux) || defined(__hpux) \
    )
#   undef DPLX_OS_HPUX
#   define DPLX_OS_HPUX DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_OS_HPUX
#   define DPLX_OS_HPUX_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_HPUX_NAME "HP-UX"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_HPUX,DPLX_OS_HPUX_NAME)

/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_IRIX_H
#define DPLX_PREDEF_OS_IRIX_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_IRIX`

http://en.wikipedia.org/wiki/Irix[IRIX] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `sgi` | {predef_detection}
| `+__sgi+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_OS_IRIX DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(sgi) || defined(__sgi) \
    )
#   undef DPLX_OS_IRIX
#   define DPLX_OS_IRIX DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_OS_IRIX
#   define DPLX_OS_IRIX_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_IRIX_NAME "IRIX"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_IRIX,DPLX_OS_IRIX_NAME)

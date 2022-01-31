/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_WINDOWS_H
#define DPLX_PREDEF_OS_WINDOWS_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_WINDOWS`

http://en.wikipedia.org/wiki/Category:Microsoft_Windows[Microsoft Windows] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+_WIN32+` | {predef_detection}
| `+_WIN64+` | {predef_detection}
| `+__WIN32__+` | {predef_detection}
| `+__TOS_WIN__+` | {predef_detection}
| `+__WINDOWS__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_OS_WINDOWS DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(_WIN32) || defined(_WIN64) || \
    defined(__WIN32__) || defined(__TOS_WIN__) || \
    defined(__WINDOWS__) \
    )
#   undef DPLX_OS_WINDOWS
#   define DPLX_OS_WINDOWS DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_OS_WINDOWS
#   define DPLX_OS_WINDOWS_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_WINDOWS_NAME "Microsoft Windows"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_WINDOWS,DPLX_OS_WINDOWS_NAME)

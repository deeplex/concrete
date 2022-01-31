/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_LINUX_H
#define DPLX_PREDEF_OS_LINUX_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_LINUX`

http://en.wikipedia.org/wiki/Linux[Linux] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `linux` | {predef_detection}
| `+__linux+` | {predef_detection}
| `+__linux__+` | {predef_detection}
| `+__gnu_linux__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_OS_LINUX DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(linux) || defined(__linux) || \
    defined(__linux__) || defined(__gnu_linux__) \
    )
#   undef DPLX_OS_LINUX
#   define DPLX_OS_LINUX DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_OS_LINUX
#   define DPLX_OS_LINUX_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_LINUX_NAME "Linux"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_LINUX,DPLX_OS_LINUX_NAME)

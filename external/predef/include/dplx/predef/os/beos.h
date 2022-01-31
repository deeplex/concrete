/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_BEOS_H
#define DPLX_PREDEF_OS_BEOS_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_BEOS`

http://en.wikipedia.org/wiki/BeOS[BeOS] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__BEOS__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_OS_BEOS DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__BEOS__) \
    )
#   undef DPLX_OS_BEOS
#   define DPLX_OS_BEOS DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_OS_BEOS
#   define DPLX_OS_BEOS_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_BEOS_NAME "BeOS"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_BEOS,DPLX_OS_BEOS_NAME)

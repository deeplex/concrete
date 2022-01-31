/*
Copyright Franz Detro 2014
Copyright Rene Rivera 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_IOS_H
#define DPLX_PREDEF_OS_IOS_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_IOS`

http://en.wikipedia.org/wiki/iOS[iOS] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__APPLE__+` | {predef_detection}
| `+__MACH__+` | {predef_detection}
| `+__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__+` | {predef_detection}

| `+__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__+` | +__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__+*1000
|===
*/ // end::reference[]

#define DPLX_OS_IOS DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__APPLE__) && defined(__MACH__) && \
    defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) \
    )
#   undef DPLX_OS_IOS
#   define DPLX_OS_IOS (__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__*1000)
#endif

#if DPLX_OS_IOS
#   define DPLX_OS_IOS_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_IOS_NAME "iOS"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_IOS,DPLX_OS_IOS_NAME)

/*
Copyright Rene Rivera 2015-2019
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_PLAT_ANDROID_H
#define DPLX_PREDEF_PLAT_ANDROID_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_PLAT_ANDROID`

http://en.wikipedia.org/wiki/Android_%28operating_system%29[Android] platform.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__ANDROID__+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_PLAT_ANDROID DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__ANDROID__)
#   undef DPLX_PLAT_ANDROID
#   define DPLX_PLAT_ANDROID DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_PLAT_ANDROID
#   define DPLX_PLAT_ANDROID_AVAILABLE
#   include <dplx/predef/detail/platform_detected.h>
#endif

#define DPLX_PLAT_ANDROID_NAME "Android"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_PLAT_ANDROID,DPLX_PLAT_ANDROID_NAME)

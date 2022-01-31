/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_PLAT_MINGW32_H
#define DPLX_PREDEF_PLAT_MINGW32_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_PLAT_MINGW32`

http://www.mingw.org/[MinGW] platform.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__MINGW32__+` | {predef_detection}

| `+__MINGW32_VERSION_MAJOR+`, `+__MINGW32_VERSION_MINOR+` | V.R.0
|===
*/ // end::reference[]

#define DPLX_PLAT_MINGW32 DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__MINGW32__)
#   include <_mingw.h>
#   if !defined(DPLX_PLAT_MINGW32_DETECTION) && (defined(__MINGW32_VERSION_MAJOR) && defined(__MINGW32_VERSION_MINOR))
#       define DPLX_PLAT_MINGW32_DETECTION \
            DPLX_VERSION_NUMBER(__MINGW32_VERSION_MAJOR,__MINGW32_VERSION_MINOR,0)
#   endif
#   if !defined(DPLX_PLAT_MINGW32_DETECTION)
#       define DPLX_PLAT_MINGW32_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef DPLX_PLAT_MINGW32_DETECTION
#   define DPLX_PLAT_MINGW32_AVAILABLE
#   if defined(DPLX_PREDEF_DETAIL_PLAT_DETECTED)
#       define DPLX_PLAT_MINGW32_EMULATED DPLX_PLAT_MINGW32_DETECTION
#   else
#       undef DPLX_PLAT_MINGW32
#       define DPLX_PLAT_MINGW32 DPLX_PLAT_MINGW32_DETECTION
#   endif
#   include <dplx/predef/detail/platform_detected.h>
#endif

#define DPLX_PLAT_MINGW32_NAME "MinGW"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_PLAT_MINGW32,DPLX_PLAT_MINGW32_NAME)

#ifdef DPLX_PLAT_MINGW32_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_PLAT_MINGW32_EMULATED,DPLX_PLAT_MINGW32_NAME)
#endif

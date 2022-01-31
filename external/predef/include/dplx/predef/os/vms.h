/*
Copyright Rene Rivera 2011-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_OS_VMS_H
#define DPLX_PREDEF_OS_VMS_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_OS_VMS`

http://en.wikipedia.org/wiki/Vms[VMS] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `VMS` | {predef_detection}
| `+__VMS+` | {predef_detection}

| `+__VMS_VER+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_OS_VMS DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(DPLX_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(VMS) || defined(__VMS) \
    )
#   undef DPLX_OS_VMS
#   if defined(__VMS_VER)
#       define DPLX_OS_VMS DPLX_PREDEF_MAKE_10_VVRR00PP00(__VMS_VER)
#   else
#       define DPLX_OS_VMS DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_OS_VMS
#   define DPLX_OS_VMS_AVAILABLE
#   include <dplx/predef/detail/os_detected.h>
#endif

#define DPLX_OS_VMS_NAME "VMS"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_OS_VMS,DPLX_OS_VMS_NAME)

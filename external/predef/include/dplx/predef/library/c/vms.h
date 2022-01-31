/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_C_VMS_H
#define DPLX_PREDEF_LIBRARY_C_VMS_H

#include <dplx/predef/library/c/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_C_VMS`

VMS libc Standard C library.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__CRTL_VER+` | {predef_detection}

| `+__CRTL_VER+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_LIB_C_VMS DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__CRTL_VER)
#   undef DPLX_LIB_C_VMS
#   define DPLX_LIB_C_VMS DPLX_PREDEF_MAKE_10_VVRR0PP00(__CRTL_VER)
#endif

#if DPLX_LIB_C_VMS
#   define DPLX_LIB_C_VMS_AVAILABLE
#endif

#define DPLX_LIB_C_VMS_NAME "VMS"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_C_VMS,DPLX_LIB_C_VMS_NAME)

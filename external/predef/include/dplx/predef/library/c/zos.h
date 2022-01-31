/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_C_ZOS_H
#define DPLX_PREDEF_LIBRARY_C_ZOS_H

#include <dplx/predef/library/c/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_C_ZOS`

z/OS libc Standard C library.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__LIBREL__+` | {predef_detection}

| `+__LIBREL__+` | V.R.P
| `+__TARGET_LIB__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_LIB_C_ZOS DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__LIBREL__)
#   undef DPLX_LIB_C_ZOS
#   if !defined(DPLX_LIB_C_ZOS) && defined(__LIBREL__)
#       define DPLX_LIB_C_ZOS DPLX_PREDEF_MAKE_0X_VRRPPPP(__LIBREL__)
#   endif
#   if !defined(DPLX_LIB_C_ZOS) && defined(__TARGET_LIB__)
#       define DPLX_LIB_C_ZOS DPLX_PREDEF_MAKE_0X_VRRPPPP(__TARGET_LIB__)
#   endif
#   if !defined(DPLX_LIB_C_ZOS)
#       define DPLX_LIB_C_ZOS DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_LIB_C_ZOS
#   define DPLX_LIB_C_ZOS_AVAILABLE
#endif

#define DPLX_LIB_C_ZOS_NAME "z/OS"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_C_ZOS,DPLX_LIB_C_ZOS_NAME)

/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_STD_MSL_H
#define DPLX_PREDEF_LIBRARY_STD_MSL_H

#include <dplx/predef/library/std/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_STD_MSL`

http://www.freescale.com/[Metrowerks] Standard {CPP} Library.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__MSL_CPP__+` | {predef_detection}
| `+__MSL__+` | {predef_detection}

| `+__MSL_CPP__+` | V.R.P
| `+__MSL__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_LIB_STD_MSL DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__MSL_CPP__) || defined(__MSL__)
#   undef DPLX_LIB_STD_MSL
#   if defined(__MSL_CPP__)
#       define DPLX_LIB_STD_MSL DPLX_PREDEF_MAKE_0X_VRPP(__MSL_CPP__)
#   else
#       define DPLX_LIB_STD_MSL DPLX_PREDEF_MAKE_0X_VRPP(__MSL__)
#   endif
#endif

#if DPLX_LIB_STD_MSL
#   define DPLX_LIB_STD_MSL_AVAILABLE
#endif

#define DPLX_LIB_STD_MSL_NAME "Metrowerks"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_STD_MSL,DPLX_LIB_STD_MSL_NAME)

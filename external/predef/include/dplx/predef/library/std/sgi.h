/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_STD_SGI_H
#define DPLX_PREDEF_LIBRARY_STD_SGI_H

#include <dplx/predef/library/std/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_STD_SGI`

http://www.sgi.com/tech/stl/[SGI] Standard {CPP} library.
If available version number as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__STL_CONFIG_H+` | {predef_detection}

| `+__SGI_STL+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_LIB_STD_SGI DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__STL_CONFIG_H)
#   undef DPLX_LIB_STD_SGI
#   if defined(__SGI_STL)
#       define DPLX_LIB_STD_SGI DPLX_PREDEF_MAKE_0X_VRP(__SGI_STL)
#   else
#       define DPLX_LIB_STD_SGI DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_LIB_STD_SGI
#   define DPLX_LIB_STD_SGI_AVAILABLE
#endif

#define DPLX_LIB_STD_SGI_NAME "SGI"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_STD_SGI,DPLX_LIB_STD_SGI_NAME)

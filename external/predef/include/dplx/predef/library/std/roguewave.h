/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_STD_ROGUEWAVE_H
#define DPLX_PREDEF_LIBRARY_STD_ROGUEWAVE_H

#include <dplx/predef/library/std/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_STD_RW`

http://stdcxx.apache.org/[Roguewave] Standard {CPP} library.
If available version number as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__STD_RWCOMPILER_H__+` | {predef_detection}
| `+_RWSTD_VER+` | {predef_detection}

| `+_RWSTD_VER+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_LIB_STD_RW DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
#   undef DPLX_LIB_STD_RW
#   if defined(_RWSTD_VER)
#       if _RWSTD_VER < 0x010000
#           define DPLX_LIB_STD_RW DPLX_PREDEF_MAKE_0X_VVRRP(_RWSTD_VER)
#       else
#           define DPLX_LIB_STD_RW DPLX_PREDEF_MAKE_0X_VVRRPP(_RWSTD_VER)
#       endif
#   else
#       define DPLX_LIB_STD_RW DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if DPLX_LIB_STD_RW
#   define DPLX_LIB_STD_RW_AVAILABLE
#endif

#define DPLX_LIB_STD_RW_NAME "Roguewave"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_STD_RW,DPLX_LIB_STD_RW_NAME)

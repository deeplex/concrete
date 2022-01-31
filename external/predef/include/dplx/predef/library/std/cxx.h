/*
Copyright Rene Rivera 2011-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_STD_CXX_H
#define DPLX_PREDEF_LIBRARY_STD_CXX_H

#include <dplx/predef/library/std/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_STD_CXX`

http://libcxx.llvm.org/[libc++] {CPP} Standard Library.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+_LIBCPP_VERSION+` | {predef_detection}

| `+_LIBCPP_VERSION+` | V.0.P
|===
*/ // end::reference[]

#define DPLX_LIB_STD_CXX DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(_LIBCPP_VERSION)
#   undef DPLX_LIB_STD_CXX
#   define DPLX_LIB_STD_CXX DPLX_PREDEF_MAKE_10_VVPPP(_LIBCPP_VERSION)
#endif

#if DPLX_LIB_STD_CXX
#   define DPLX_LIB_STD_CXX_AVAILABLE
#endif

#define DPLX_LIB_STD_CXX_NAME "libc++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_STD_CXX,DPLX_LIB_STD_CXX_NAME)

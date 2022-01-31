/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_STD_LIBCOMO_H
#define DPLX_PREDEF_LIBRARY_STD_LIBCOMO_H

#include <dplx/predef/library/std/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_STD_COMO`

http://www.comeaucomputing.com/libcomo/[Comeau Computing] Standard {CPP} Library.
Version number available as major.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__LIBCOMO__+` | {predef_detection}

| `+__LIBCOMO_VERSION__+` | V.0.0
|===
*/ // end::reference[]

#define DPLX_LIB_STD_COMO DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__LIBCOMO__)
#   undef DPLX_LIB_STD_COMO
#   define DPLX_LIB_STD_COMO DPLX_VERSION_NUMBER(__LIBCOMO_VERSION__,0,0)
#endif

#if DPLX_LIB_STD_COMO
#   define DPLX_LIB_STD_COMO_AVAILABLE
#endif

#define DPLX_LIB_STD_COMO_NAME "Comeau Computing"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_STD_COMO,DPLX_LIB_STD_COMO_NAME)

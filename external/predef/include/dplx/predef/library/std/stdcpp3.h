/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_STD_STDCPP3_H
#define DPLX_PREDEF_LIBRARY_STD_STDCPP3_H

#include <dplx/predef/library/std/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_STD_GNU`

https://gcc.gnu.org/onlinedocs/libstdc%2b%2b/[GNU libstdc++] Standard {CPP} library.
Version number available as year (from 1970), month, and day.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__GLIBCXX__+` | {predef_detection}
| `+__GLIBCPP__+` | {predef_detection}

| `+__GLIBCXX__+` | V.R.P
| `+__GLIBCPP__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_LIB_STD_GNU DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__GLIBCPP__) || defined(__GLIBCXX__)
#   undef DPLX_LIB_STD_GNU
#   if defined(__GLIBCXX__)
#       define DPLX_LIB_STD_GNU DPLX_PREDEF_MAKE_YYYYMMDD(__GLIBCXX__)
#   else
#       define DPLX_LIB_STD_GNU DPLX_PREDEF_MAKE_YYYYMMDD(__GLIBCPP__)
#   endif
#endif

#if DPLX_LIB_STD_GNU
#   define DPLX_LIB_STD_GNU_AVAILABLE
#endif

#define DPLX_LIB_STD_GNU_NAME "GNU"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_STD_GNU,DPLX_LIB_STD_GNU_NAME)

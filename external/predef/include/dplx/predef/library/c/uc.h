/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_C_UC_H
#define DPLX_PREDEF_LIBRARY_C_UC_H

#include <dplx/predef/library/c/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_C_UC`

http://en.wikipedia.org/wiki/Uclibc[uClibc] Standard C library.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__UCLIBC__+` | {predef_detection}

| `+__UCLIBC_MAJOR__+`, `+__UCLIBC_MINOR__+`, `+__UCLIBC_SUBLEVEL__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_LIB_C_UC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__UCLIBC__)
#   undef DPLX_LIB_C_UC
#   define DPLX_LIB_C_UC DPLX_VERSION_NUMBER(\
        __UCLIBC_MAJOR__,__UCLIBC_MINOR__,__UCLIBC_SUBLEVEL__)
#endif

#if DPLX_LIB_C_UC
#   define DPLX_LIB_C_UC_AVAILABLE
#endif

#define DPLX_LIB_C_UC_NAME "uClibc"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_C_UC,DPLX_LIB_C_UC_NAME)

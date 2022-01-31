/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_LIBRARY_STD_MODENA_H
#define DPLX_PREDEF_LIBRARY_STD_MODENA_H

#include <dplx/predef/library/std/_prefix.h>

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_LIB_STD_MSIPL`

http://modena.us/[Modena Software Lib++] Standard {CPP} Library.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `MSIPL_COMPILE_H` | {predef_detection}
| `+__MSIPL_COMPILE_H+` | {predef_detection}
|===
*/ // end::reference[]

#define DPLX_LIB_STD_MSIPL DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(MSIPL_COMPILE_H) || defined(__MSIPL_COMPILE_H)
#   undef DPLX_LIB_STD_MSIPL
#   define DPLX_LIB_STD_MSIPL DPLX_VERSION_NUMBER_AVAILABLE
#endif

#if DPLX_LIB_STD_MSIPL
#   define DPLX_LIB_STD_MSIPL_AVAILABLE
#endif

#define DPLX_LIB_STD_MSIPL_NAME "Modena Software Lib++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_LIB_STD_MSIPL,DPLX_LIB_STD_MSIPL_NAME)

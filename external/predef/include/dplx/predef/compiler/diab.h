/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_DIAB_H
#define DPLX_PREDEF_COMPILER_DIAB_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_DIAB`

http://www.windriver.com/products/development_suite/wind_river_compiler/[Diab C/{CPP}] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__DCC__+` | {predef_detection}

| `+__VERSION_NUMBER__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_DIAB DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__DCC__)
#   define DPLX_COMP_DIAB_DETECTION DPLX_PREDEF_MAKE_10_VRPP(__VERSION_NUMBER__)
#endif

#ifdef DPLX_COMP_DIAB_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_DIAB_EMULATED DPLX_COMP_DIAB_DETECTION
#   else
#       undef DPLX_COMP_DIAB
#       define DPLX_COMP_DIAB DPLX_COMP_DIAB_DETECTION
#   endif
#   define DPLX_COMP_DIAB_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_DIAB_NAME "Diab C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_DIAB,DPLX_COMP_DIAB_NAME)

#ifdef DPLX_COMP_DIAB_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_DIAB_EMULATED,DPLX_COMP_DIAB_NAME)
#endif

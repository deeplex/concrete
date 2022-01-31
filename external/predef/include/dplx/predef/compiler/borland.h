/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_BORLAND_H
#define DPLX_PREDEF_COMPILER_BORLAND_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_BORLAND`

http://en.wikipedia.org/wiki/C_plus_plus_builder[Borland {CPP}] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__BORLANDC__+` | {predef_detection}
| `+__CODEGEARC__+` | {predef_detection}

| `+__BORLANDC__+` | V.R.P
| `+__CODEGEARC__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_BORLAND DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__BORLANDC__) || defined(__CODEGEARC__)
#   if !defined(DPLX_COMP_BORLAND_DETECTION) && (defined(__CODEGEARC__))
#       define DPLX_COMP_BORLAND_DETECTION DPLX_PREDEF_MAKE_0X_VVRP(__CODEGEARC__)
#   endif
#   if !defined(DPLX_COMP_BORLAND_DETECTION)
#       define DPLX_COMP_BORLAND_DETECTION DPLX_PREDEF_MAKE_0X_VVRP(__BORLANDC__)
#   endif
#endif

#ifdef DPLX_COMP_BORLAND_DETECTION
#   define DPLX_COMP_BORLAND_AVAILABLE
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_BORLAND_EMULATED DPLX_COMP_BORLAND_DETECTION
#   else
#       undef DPLX_COMP_BORLAND
#       define DPLX_COMP_BORLAND DPLX_COMP_BORLAND_DETECTION
#   endif
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_BORLAND_NAME "Borland C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_BORLAND,DPLX_COMP_BORLAND_NAME)

#ifdef DPLX_COMP_BORLAND_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_BORLAND_EMULATED,DPLX_COMP_BORLAND_NAME)
#endif

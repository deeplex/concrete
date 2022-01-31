/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_SGI_MIPSPRO_H
#define DPLX_PREDEF_COMPILER_SGI_MIPSPRO_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_SGI`

http://en.wikipedia.org/wiki/MIPSpro[SGI MIPSpro] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__sgi+` | {predef_detection}
| `sgi` | {predef_detection}

| `+_SGI_COMPILER_VERSION+` | V.R.P
| `+_COMPILER_VERSION+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_SGI DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__sgi) || defined(sgi)
#   if !defined(DPLX_COMP_SGI_DETECTION) && defined(_SGI_COMPILER_VERSION)
#       define DPLX_COMP_SGI_DETECTION DPLX_PREDEF_MAKE_10_VRP(_SGI_COMPILER_VERSION)
#   endif
#   if !defined(DPLX_COMP_SGI_DETECTION) && defined(_COMPILER_VERSION)
#       define DPLX_COMP_SGI_DETECTION DPLX_PREDEF_MAKE_10_VRP(_COMPILER_VERSION)
#   endif
#   if !defined(DPLX_COMP_SGI_DETECTION)
#       define DPLX_COMP_SGI_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef DPLX_COMP_SGI_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_SGI_EMULATED DPLX_COMP_SGI_DETECTION
#   else
#       undef DPLX_COMP_SGI
#       define DPLX_COMP_SGI DPLX_COMP_SGI_DETECTION
#   endif
#   define DPLX_COMP_SGI_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_SGI_NAME "SGI MIPSpro"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_SGI,DPLX_COMP_SGI_NAME)

#ifdef DPLX_COMP_SGI_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_SGI_EMULATED,DPLX_COMP_SGI_NAME)
#endif

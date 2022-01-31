/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_MPW_H
#define DPLX_PREDEF_COMPILER_MPW_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_MPW`

http://en.wikipedia.org/wiki/Macintosh_Programmer%27s_Workshop[MPW {CPP}] compiler.
Version number available as major, and minor.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__MRC__+` | {predef_detection}
| `MPW_C` | {predef_detection}
| `MPW_CPLUS` | {predef_detection}

| `+__MRC__+` | V.R.0
|===
*/ // end::reference[]

#define DPLX_COMP_MPW DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__MRC__) || defined(MPW_C) || defined(MPW_CPLUS)
#   if !defined(DPLX_COMP_MPW_DETECTION) && defined(__MRC__)
#       define DPLX_COMP_MPW_DETECTION DPLX_PREDEF_MAKE_0X_VVRR(__MRC__)
#   endif
#   if !defined(DPLX_COMP_MPW_DETECTION)
#       define DPLX_COMP_MPW_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef DPLX_COMP_MPW_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_MPW_EMULATED DPLX_COMP_MPW_DETECTION
#   else
#       undef DPLX_COMP_MPW
#       define DPLX_COMP_MPW DPLX_COMP_MPW_DETECTION
#   endif
#   define DPLX_COMP_MPW_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_MPW_NAME "MPW C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_MPW,DPLX_COMP_MPW_NAME)

#ifdef DPLX_COMP_MPW_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_MPW_EMULATED,DPLX_COMP_MPW_NAME)
#endif

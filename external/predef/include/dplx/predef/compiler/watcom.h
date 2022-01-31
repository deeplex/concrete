/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_WATCOM_H
#define DPLX_PREDEF_COMPILER_WATCOM_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_WATCOM`

http://en.wikipedia.org/wiki/Watcom[Watcom {CPP}] compiler.
Version number available as major, and minor.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__WATCOMC__+` | {predef_detection}

| `+__WATCOMC__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_WATCOM DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__WATCOMC__)
#   define DPLX_COMP_WATCOM_DETECTION DPLX_PREDEF_MAKE_10_VVRR(__WATCOMC__)
#endif

#ifdef DPLX_COMP_WATCOM_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_WATCOM_EMULATED DPLX_COMP_WATCOM_DETECTION
#   else
#       undef DPLX_COMP_WATCOM
#       define DPLX_COMP_WATCOM DPLX_COMP_WATCOM_DETECTION
#   endif
#   define DPLX_COMP_WATCOM_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_WATCOM_NAME "Watcom C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_WATCOM,DPLX_COMP_WATCOM_NAME)

#ifdef DPLX_COMP_WATCOM_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_WATCOM_EMULATED,DPLX_COMP_WATCOM_NAME)
#endif

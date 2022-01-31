/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_IAR_H
#define DPLX_PREDEF_COMPILER_IAR_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_IAR`

IAR C/{CPP} compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__IAR_SYSTEMS_ICC__+` | {predef_detection}

| `+__VER__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_IAR DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__IAR_SYSTEMS_ICC__)
#   define DPLX_COMP_IAR_DETECTION DPLX_PREDEF_MAKE_10_VVRR(__VER__)
#endif

#ifdef DPLX_COMP_IAR_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_IAR_EMULATED DPLX_COMP_IAR_DETECTION
#   else
#       undef DPLX_COMP_IAR
#       define DPLX_COMP_IAR DPLX_COMP_IAR_DETECTION
#   endif
#   define DPLX_COMP_IAR_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_IAR_NAME "IAR C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_IAR,DPLX_COMP_IAR_NAME)

#ifdef DPLX_COMP_IAR_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_IAR_EMULATED,DPLX_COMP_IAR_NAME)
#endif

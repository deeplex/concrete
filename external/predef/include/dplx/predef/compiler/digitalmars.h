/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_DIGITALMARS_H
#define DPLX_PREDEF_COMPILER_DIGITALMARS_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_DMC`

http://en.wikipedia.org/wiki/Digital_Mars[Digital Mars] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__DMC__+` | {predef_detection}

| `+__DMC__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_DMC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__DMC__)
#   define DPLX_COMP_DMC_DETECTION DPLX_PREDEF_MAKE_0X_VRP(__DMC__)
#endif

#ifdef DPLX_COMP_DMC_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_DMC_EMULATED DPLX_COMP_DMC_DETECTION
#   else
#       undef DPLX_COMP_DMC
#       define DPLX_COMP_DMC DPLX_COMP_DMC_DETECTION
#   endif
#   define DPLX_COMP_DMC_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_DMC_NAME "Digital Mars"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_DMC,DPLX_COMP_DMC_NAME)

#ifdef DPLX_COMP_DMC_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_DMC_EMULATED,DPLX_COMP_DMC_NAME)
#endif

/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_PALM_H
#define DPLX_PREDEF_COMPILER_PALM_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_PALM`

Palm C/{CPP} compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+_PACC_VER+` | {predef_detection}

| `+_PACC_VER+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_PALM DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(_PACC_VER)
#   define DPLX_COMP_PALM_DETECTION DPLX_PREDEF_MAKE_0X_VRRPP000(_PACC_VER)
#endif

#ifdef DPLX_COMP_PALM_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_PALM_EMULATED DPLX_COMP_PALM_DETECTION
#   else
#       undef DPLX_COMP_PALM
#       define DPLX_COMP_PALM DPLX_COMP_PALM_DETECTION
#   endif
#   define DPLX_COMP_PALM_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_PALM_NAME "Palm C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_PALM,DPLX_COMP_PALM_NAME)

#ifdef DPLX_COMP_PALM_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_PALM_EMULATED,DPLX_COMP_PALM_NAME)
#endif

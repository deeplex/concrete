/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_KAI_H
#define DPLX_PREDEF_COMPILER_KAI_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_KCC`

Kai {CPP} compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__KCC+` | {predef_detection}

| `+__KCC_VERSION+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_KCC DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__KCC)
#   define DPLX_COMP_KCC_DETECTION DPLX_PREDEF_MAKE_0X_VRPP(__KCC_VERSION)
#endif

#ifdef DPLX_COMP_KCC_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_KCC_EMULATED DPLX_COMP_KCC_DETECTION
#   else
#       undef DPLX_COMP_KCC
#       define DPLX_COMP_KCC DPLX_COMP_KCC_DETECTION
#   endif
#   define DPLX_COMP_KCC_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_KCC_NAME "Kai C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_KCC,DPLX_COMP_KCC_NAME)

#ifdef DPLX_COMP_KCC_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_KCC_EMULATED,DPLX_COMP_KCC_NAME)
#endif

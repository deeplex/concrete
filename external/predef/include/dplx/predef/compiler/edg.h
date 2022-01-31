/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_EDG_H
#define DPLX_PREDEF_COMPILER_EDG_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_EDG`

http://en.wikipedia.org/wiki/Edison_Design_Group[EDG {CPP} Frontend] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__EDG__+` | {predef_detection}

| `+__EDG_VERSION__+` | V.R.0
|===
*/ // end::reference[]

#define DPLX_COMP_EDG DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__EDG__)
#   define DPLX_COMP_EDG_DETECTION DPLX_PREDEF_MAKE_10_VRR(__EDG_VERSION__)
#endif

#ifdef DPLX_COMP_EDG_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_EDG_EMULATED DPLX_COMP_EDG_DETECTION
#   else
#       undef DPLX_COMP_EDG
#       define DPLX_COMP_EDG DPLX_COMP_EDG_DETECTION
#   endif
#   define DPLX_COMP_EDG_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_EDG_NAME "EDG C++ Frontend"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_EDG,DPLX_COMP_EDG_NAME)

#ifdef DPLX_COMP_EDG_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_EDG_EMULATED,DPLX_COMP_EDG_NAME)
#endif

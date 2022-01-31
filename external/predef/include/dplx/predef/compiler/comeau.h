/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_COMEAU_H
#define DPLX_PREDEF_COMPILER_COMEAU_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

#define DPLX_COMP_COMO DPLX_VERSION_NUMBER_NOT_AVAILABLE

/* tag::reference[]
= `DPLX_COMP_COMO`

http://en.wikipedia.org/wiki/Comeau_C/C%2B%2B[Comeau {CPP}] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__COMO__+` | {predef_detection}

| `+__COMO_VERSION__+` | V.R.P
|===
*/ // end::reference[]

#if defined(__COMO__)
#   if !defined(DPLX_COMP_COMO_DETECTION) && defined(__COMO_VERSION__)
#       define DPLX_COMP_COMO_DETECTION DPLX_PREDEF_MAKE_0X_VRP(__COMO_VERSION__)
#   endif
#   if !defined(DPLX_COMP_COMO_DETECTION)
#       define DPLX_COMP_COMO_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef DPLX_COMP_COMO_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_COMO_EMULATED DPLX_COMP_COMO_DETECTION
#   else
#       undef DPLX_COMP_COMO
#       define DPLX_COMP_COMO DPLX_COMP_COMO_DETECTION
#   endif
#   define DPLX_COMP_COMO_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_COMO_NAME "Comeau C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_COMO,DPLX_COMP_COMO_NAME)

#ifdef DPLX_COMP_COMO_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_COMO_EMULATED,DPLX_COMP_COMO_NAME)
#endif

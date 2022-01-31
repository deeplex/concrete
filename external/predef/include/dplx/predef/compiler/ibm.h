/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_IBM_H
#define DPLX_PREDEF_COMPILER_IBM_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_IBM`

http://en.wikipedia.org/wiki/VisualAge[IBM XL C/{CPP}] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__IBMCPP__+` | {predef_detection}
| `+__xlC__+` | {predef_detection}
| `+__xlc__+` | {predef_detection}

| `+__COMPILER_VER__+` | V.R.P
| `+__xlC__+` | V.R.P
| `+__xlc__+` | V.R.P
| `+__IBMCPP__+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_IBM DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__IBMCPP__) || defined(__xlC__) || defined(__xlc__)
#   if !defined(DPLX_COMP_IBM_DETECTION) && defined(__COMPILER_VER__)
#       define DPLX_COMP_IBM_DETECTION DPLX_PREDEF_MAKE_0X_VRRPPPP(__COMPILER_VER__)
#   endif
#   if !defined(DPLX_COMP_IBM_DETECTION) && defined(__xlC__)
#       define DPLX_COMP_IBM_DETECTION DPLX_PREDEF_MAKE_0X_VVRR(__xlC__)
#   endif
#   if !defined(DPLX_COMP_IBM_DETECTION) && defined(__xlc__)
#       define DPLX_COMP_IBM_DETECTION DPLX_PREDEF_MAKE_0X_VVRR(__xlc__)
#   endif
#   if !defined(DPLX_COMP_IBM_DETECTION)
#       define DPLX_COMP_IBM_DETECTION DPLX_PREDEF_MAKE_10_VRP(__IBMCPP__)
#   endif
#endif

#ifdef DPLX_COMP_IBM_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_IBM_EMULATED DPLX_COMP_IBM_DETECTION
#   else
#       undef DPLX_COMP_IBM
#       define DPLX_COMP_IBM DPLX_COMP_IBM_DETECTION
#   endif
#   define DPLX_COMP_IBM_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_IBM_NAME "IBM XL C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_IBM,DPLX_COMP_IBM_NAME)

#ifdef DPLX_COMP_IBM_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_IBM_EMULATED,DPLX_COMP_IBM_NAME)
#endif

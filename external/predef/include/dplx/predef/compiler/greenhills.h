/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_GREENHILLS_H
#define DPLX_PREDEF_COMPILER_GREENHILLS_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_GHS`

http://en.wikipedia.org/wiki/Green_Hills_Software[Green Hills C/{CPP}] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__ghs+` | {predef_detection}
| `+__ghs__+` | {predef_detection}

| `+__GHS_VERSION_NUMBER__+` | V.R.P
| `+__ghs+` | V.R.P
|===
*/ // end::reference[]

#define DPLX_COMP_GHS DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__ghs) || defined(__ghs__)
#   if !defined(DPLX_COMP_GHS_DETECTION) && defined(__GHS_VERSION_NUMBER__)
#       define DPLX_COMP_GHS_DETECTION DPLX_PREDEF_MAKE_10_VRP(__GHS_VERSION_NUMBER__)
#   endif
#   if !defined(DPLX_COMP_GHS_DETECTION) && defined(__ghs)
#       define DPLX_COMP_GHS_DETECTION DPLX_PREDEF_MAKE_10_VRP(__ghs)
#   endif
#   if !defined(DPLX_COMP_GHS_DETECTION)
#       define DPLX_COMP_GHS_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef DPLX_COMP_GHS_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_GHS_EMULATED DPLX_COMP_GHS_DETECTION
#   else
#       undef DPLX_COMP_GHS
#       define DPLX_COMP_GHS DPLX_COMP_GHS_DETECTION
#   endif
#   define DPLX_COMP_GHS_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_GHS_NAME "Green Hills C/C++"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_GHS,DPLX_COMP_GHS_NAME)

#ifdef DPLX_COMP_GHS_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_GHS_EMULATED,DPLX_COMP_GHS_NAME)
#endif

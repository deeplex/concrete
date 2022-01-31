/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef DPLX_PREDEF_COMPILER_METROWERKS_H
#define DPLX_PREDEF_COMPILER_METROWERKS_H

#include <dplx/predef/version_number.h>
#include <dplx/predef/make.h>

/* tag::reference[]
= `DPLX_COMP_MWERKS`

http://en.wikipedia.org/wiki/CodeWarrior[Metrowerks CodeWarrior] compiler.
Version number available as major, minor, and patch.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__MWERKS__+` | {predef_detection}
| `+__CWCC__+` | {predef_detection}

| `+__CWCC__+` | V.R.P
| `+__MWERKS__+` | V.R.P >= 4.2.0
| `+__MWERKS__+` | 9.R.0
| `+__MWERKS__+` | 8.R.0
|===
*/ // end::reference[]

#define DPLX_COMP_MWERKS DPLX_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__MWERKS__) || defined(__CWCC__)
#   if !defined(DPLX_COMP_MWERKS_DETECTION) && defined(__CWCC__)
#       define DPLX_COMP_MWERKS_DETECTION DPLX_PREDEF_MAKE_0X_VRPP(__CWCC__)
#   endif
#   if !defined(DPLX_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x4200)
#       define DPLX_COMP_MWERKS_DETECTION DPLX_PREDEF_MAKE_0X_VRPP(__MWERKS__)
#   endif
#   if !defined(DPLX_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x3204) // note the "skip": 04->9.3
#       define DPLX_COMP_MWERKS_DETECTION DPLX_VERSION_NUMBER(9,(__MWERKS__)%100-1,0)
#   endif
#   if !defined(DPLX_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x3200)
#       define DPLX_COMP_MWERKS_DETECTION DPLX_VERSION_NUMBER(9,(__MWERKS__)%100,0)
#   endif
#   if !defined(DPLX_COMP_MWERKS_DETECTION) && (__MWERKS__ >= 0x3000)
#       define DPLX_COMP_MWERKS_DETECTION DPLX_VERSION_NUMBER(8,(__MWERKS__)%100,0)
#   endif
#   if !defined(DPLX_COMP_MWERKS_DETECTION)
#       define DPLX_COMP_MWERKS_DETECTION DPLX_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef DPLX_COMP_MWERKS_DETECTION
#   if defined(DPLX_PREDEF_DETAIL_COMP_DETECTED)
#       define DPLX_COMP_MWERKS_EMULATED DPLX_COMP_MWERKS_DETECTION
#   else
#       undef DPLX_COMP_MWERKS
#       define DPLX_COMP_MWERKS DPLX_COMP_MWERKS_DETECTION
#   endif
#   define DPLX_COMP_MWERKS_AVAILABLE
#   include <dplx/predef/detail/comp_detected.h>
#endif

#define DPLX_COMP_MWERKS_NAME "Metrowerks CodeWarrior"

#endif

#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_MWERKS,DPLX_COMP_MWERKS_NAME)

#ifdef DPLX_COMP_MWERKS_EMULATED
#include <dplx/predef/detail/test.h>
DPLX_PREDEF_DECLARE_TEST(DPLX_COMP_MWERKS_EMULATED,DPLX_COMP_MWERKS_NAME)
#endif
